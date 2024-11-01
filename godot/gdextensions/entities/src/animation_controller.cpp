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
#include "entities/error.hpp"

using namespace entities;

godot::PackedStringArray
AnimationController::_get_configuration_warnings() const {
  godot::PackedStringArray warnings;

  if (!_text) {
    warnings.push_back("Text should be set");
  }

  return warnings;
}

void AnimationController::ready() {
  if (godot::Engine::get_singleton()->is_editor_hint()) {
    return;
  }

  if (!_text) {
    throw PropertyNotSetError("text", "TextAnimator");
  }

  _text->connect(TextAnimator::SignalName::AnimationEnd,
                 godot::Callable(this, "_text_animation_ended"));

  _timer = memnew(godot::Timer);
  _timer->set_wait_time(1.0);
  _timer->set_one_shot(true);
  _timer->connect("timeout", godot::Callable(this, "_switch_text"));
  add_child(_timer);
  _timer->start();
}

void AnimationController::_switch_text() { _text->switch_text(); }

void AnimationController::_text_animation_ended() { _timer->start(); }
