#ifndef __ENTITIES_ANIMATION_CONTROLLER_HPP
#define __ENTITIES_ANIMATION_CONTROLLER_HPP

#include <vector>

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/signal.hpp>
#include <godot_cpp/variant/typed_array.hpp>

#include "entities/animated_text.hpp"

namespace entities {

class AnimationController : public godot::Node {
  GDCLASS(AnimationController, Node)

public:
  typedef godot::TypedArray<godot::NodePath> TextPathArray;
  typedef std::vector<AnimatedText *> TextNodeArray;
  enum State {
    Idle,
    TextSwitching,
    AnimationRunning,
  };
  struct SignalName {
    static constexpr char *StartSwitchText = (char *)"start_switch_text";
    static constexpr char *StartNewAnimation = (char *)"start_new_animation";
  };

  AnimationController() = default;
  ~AnimationController() = default;
  AnimationController(AnimationController const &) = delete;

  // Override
  godot::PackedStringArray _get_configuration_warnings() const override;
  void _ready() override;

  void switch_text_ended();
  void animation_ended();

private:
  // Properties
  godot::Timer *_timer = nullptr;
  State _last_state = State::Idle;

  // Methods
  void _timer_timeout();
  void _switch_text();
  void _start_new_animation();

  static void _bind_methods() {
    ADD_SIGNAL({SignalName::StartSwitchText});
    ADD_SIGNAL({SignalName::StartNewAnimation});

    godot::ClassDB::bind_method(godot::D_METHOD("switch_text_ended"),
                                &AnimationController::switch_text_ended);
    godot::ClassDB::bind_method(godot::D_METHOD("animation_ended"),
                                &AnimationController::animation_ended);
    godot::ClassDB::bind_method(godot::D_METHOD("_timer_timeout"),
                                &AnimationController::_timer_timeout);
  }
};

} // namespace entities

#endif
