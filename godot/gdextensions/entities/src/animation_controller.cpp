#include <stdexcept>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "entities/animated_text.hpp"
#include "entities/animation_controller.hpp"
#include "entities/error.hpp"

using namespace entities;

godot::PackedStringArray
AnimationController::_get_configuration_warnings() const {
  godot::PackedStringArray warnings;

  if (_texts.is_empty()) {
    warnings.push_back("Texts is empty");
  }

  return warnings;
}

void AnimationController::_ready() {
  if (godot::Engine::get_singleton()->is_editor_hint()) {
    return;
  }

  if (_texts.is_empty()) {
    throw PropertyNotSetError("texts", "AnimatedText[]");
  }

  _start_text_animation();
}

AnimatedText *AnimationController::_get_text(uint32_t text_idx) const {
  godot::NodePath animated_text_path = _texts[_current_text_idx];
  AnimatedText *animated_text = get_node<AnimatedText>(animated_text_path);
  if (!animated_text) {
    throw std::runtime_error("expect to be AnimatedText");
  }

  return animated_text;
}

void AnimationController::text_animation_ended(
    AnimatedText::AnimationState animation_state, uint32_t text_idx) {
  if (text_idx >= _texts.size()) {
    throw std::runtime_error("text_idx expect to be in bound");
  }

  AnimatedText *animated_text = _get_text(text_idx);

  animated_text->disconnect(AnimatedText::SignalName::AnimationEnded,
                            godot::Callable(this, "text_animation_ended"));

  if (animation_state == AnimatedText::AnimationState::Disappear) {
    if (++_current_text_idx >= _texts.size()) {
      _current_text_idx = 0;
    }
  }

  _start_text_animation();
}

void AnimationController::_start_text_animation() {
  if (_current_text_idx >= _texts.size()) {
    throw std::runtime_error("_current_text_idx expect to be in bound");
  }

  AnimatedText *animated_text = _get_text(_current_text_idx);

  animated_text->connect(
      AnimatedText::SignalName::AnimationEnded,
      godot::Callable(this, "text_animation_ended").bind(_current_text_idx),
      CONNECT_DEFERRED);
  animated_text->start_animation();
}
