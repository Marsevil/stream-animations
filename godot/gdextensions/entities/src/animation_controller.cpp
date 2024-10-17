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

  if (_text_paths.is_empty()) {
    warnings.push_back("Texts is empty");
  }

  return warnings;
}

void AnimationController::_ready() {
  if (godot::Engine::get_singleton()->is_editor_hint()) {
    return;
  }

  if (_text_paths.is_empty()) {
    throw PropertyNotSetError("texts", "AnimatedText[]");
  }

  _texts.reserve(_text_paths.size());
  for (uint32_t text_idx = 0; text_idx < _text_paths.size(); ++text_idx) {
    AnimatedText *text = _get_text(text_idx);
    text->connect(AnimatedText::SignalName::AnimationEnded,
                  godot::Callable(this, "text_animation_ended").bind(text_idx),
                  CONNECT_DEFERRED);
    _texts.push_back(text);
  }

  _start_text_animation();
}

AnimatedText *AnimationController::_get_text(uint32_t text_idx) const {
  if (text_idx >= _text_paths.size()) {
    throw std::runtime_error("expect to be in bound");
  }

  godot::NodePath animated_text_path = _text_paths[text_idx];
  AnimatedText *animated_text = get_node<AnimatedText>(animated_text_path);
  if (!animated_text) {
    throw std::runtime_error("expect to be AnimatedText");
  }

  return animated_text;
}

void AnimationController::text_animation_ended(
    AnimatedText::AnimationState animation_state, uint32_t text_idx) {
  if (animation_state == AnimatedText::AnimationState::Disappear) {
    if (++_current_text_idx >= _texts.size()) {
      _current_text_idx = 0;
    }
  }

  _start_text_animation();
}

void AnimationController::_start_text_animation() {
  AnimatedText *animated_text = _texts.at(_current_text_idx);
  animated_text->start_animation();
}
