#ifndef __ENTITIES_ANIMATED_TEXT_HPP
#define __ENTITIES_ANIMATED_TEXT_HPP

#include <optional>

#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/string.hpp>

namespace entities {

class AnimatedText : public godot::Label {
  GDCLASS(AnimatedText, Label)

public:
  struct SignalName {
    static constexpr char *AnimationAppearStarted =
        (char *)"AnimationAppearStarted";
    static constexpr char *AnimationDisappearStarted =
        (char *)"AnimationDisappearStarted";
    static constexpr char *AnimationAppearEnded =
        (char *)"AnimationAppearEnded";
    static constexpr char *AnimationDisappearEnded =
        (char *)"AnimationDisappearEnded";
  };

  enum AnimationState { Appear, Disappear };

  struct AnimationData {
    AnimationState state;
    double elapsed_time = 0.0;
  };

  AnimatedText();
  ~AnimatedText() = default;
  AnimatedText(const AnimatedText &) = delete;

  void _ready() override;
  void _process(double delta) override;

  inline void set_animation_time(double value) { _animation_time = value; }
  inline double get_animation_time() { return _animation_time; }

  void start_appear_animation();
  void start_disappear_animation();

private:
  double _animation_time = 1.0;

  std::optional<AnimationData> _animation_data = std::nullopt;

  void _end_animation();

  static void _bind_methods() {
    ADD_SIGNAL(
        godot::MethodInfo(AnimatedText::SignalName::AnimationAppearStarted));
    ADD_SIGNAL(
        godot::MethodInfo(AnimatedText::SignalName::AnimationDisappearStarted));
    ADD_SIGNAL(
        godot::MethodInfo(AnimatedText::SignalName::AnimationAppearEnded));
    ADD_SIGNAL(
        godot::MethodInfo(AnimatedText::SignalName::AnimationDisappearEnded));

    godot::ClassDB::bind_method(godot::D_METHOD("set_animation_time"),
                                &AnimatedText::set_animation_time);
    godot::ClassDB::bind_method(godot::D_METHOD("get_animation_time"),
                                &AnimatedText::get_animation_time);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "animation_time"),
                 "set_animation_time", "get_animation_time");

    godot::ClassDB::bind_method(godot::D_METHOD("start_appear_animation"),
                                &AnimatedText::start_appear_animation);
    godot::ClassDB::bind_method(godot::D_METHOD("start_disappear_animation"),
                                &AnimatedText::start_disappear_animation);

    BIND_ENUM_CONSTANT(AnimationState::Appear);
    BIND_ENUM_CONSTANT(AnimationState::Disappear);
  }
};

} // namespace entities

VARIANT_ENUM_CAST(entities::AnimatedText::AnimationState);

#endif // __ENTITIES_ANIMATED_TEXT_HPP
