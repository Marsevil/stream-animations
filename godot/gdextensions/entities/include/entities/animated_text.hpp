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
    static constexpr char *AnimationStarted = (char *)"AnimationStarted";
    static constexpr char *AnimationEnded = (char *)"AnimationEnded";
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

  void start_animation();
  void end_animation();

private:
  double _animation_time = 1.0;

  std::optional<AnimationData> _animation_data = std::nullopt;

  static void _bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("set_animation_time"),
                                &AnimatedText::set_animation_time);
    godot::ClassDB::bind_method(godot::D_METHOD("get_animation_time"),
                                &AnimatedText::get_animation_time);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "animation_time"),
                 "set_animation_time", "get_animation_time");

    godot::ClassDB::bind_method(godot::D_METHOD("start_animation"),
                                &AnimatedText::start_animation);
    godot::ClassDB::bind_method(godot::D_METHOD("end_animation"),
                                &AnimatedText::end_animation);

    ADD_SIGNAL(godot::MethodInfo(
        AnimatedText::SignalName::AnimationEnded,
        godot::PropertyInfo(godot::Variant::INT, "animation_state")));

    BIND_ENUM_CONSTANT(AnimationState::Appear);
    BIND_ENUM_CONSTANT(AnimationState::Disappear);
  }
};

} // namespace entities

VARIANT_ENUM_CAST(entities::AnimatedText::AnimationState);

#endif // __ENTITIES_ANIMATED_TEXT_HPP
