#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "entities/animation_controller.hpp"

using namespace entities;

godot::PackedStringArray
AnimationController::_get_configuration_warnings() const {
  godot::PackedStringArray warnings;

  return warnings;
}

void AnimationController::_ready() {
  if (godot::Engine::get_singleton()->is_editor_hint()) {
    return;
  }

  _timer = memnew(godot::Timer);
  _timer->set_wait_time(1.0);
  _timer->set_one_shot(true);
  _timer->connect("timeout", godot::Callable(this, "_timer_timeout"));
  add_child(_timer);
  _timer->start();
}

void AnimationController::_switch_text() {
  _last_state = State::TextSwitching;
  emit_signal(SignalName::StartSwitchText);
}

void AnimationController::_start_new_animation() {
  _last_state = State::AnimationRunning;
  emit_signal(SignalName::StartNewAnimation);
}

void AnimationController::_timer_timeout() {
  switch (_last_state) {
  case State::Idle:
  case State::TextSwitching:
    _start_new_animation();
    break;
  case State::AnimationRunning:
    _switch_text();
    break;
  }
}

void AnimationController::switch_text_ended() { _timer->start(); }

void AnimationController::animation_ended() { _timer->start(); }
