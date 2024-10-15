#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/callable.hpp>

#include "entities/animation_controller.hpp"

using namespace entities;

void AnimationController::_ready() {
  if (godot::Engine::get_singleton()->is_editor_hint()) {
    return;
  }

  restart_text_animation();
}

void AnimationController::restart_text_animation() {
  emit_signal(AnimationController::SignalName::StartTextAnimation);
}

void AnimationController::_bind_methods() {
  godot::ClassDB::bind_method(godot::D_METHOD("restart_text_animation"),
                              &AnimationController::restart_text_animation);

  ADD_SIGNAL(
      godot::MethodInfo(AnimationController::SignalName::StartTextAnimation));
}
