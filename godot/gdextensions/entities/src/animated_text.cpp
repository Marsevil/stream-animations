#include <cassert>
#include <cstdint>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/callable_custom.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <stdexcept>

#include "entities/animated_text.hpp"
#include "entities/error.hpp"

using namespace entities;

AnimatedText::AnimatedText() { this->set_visible_characters(0); }

void AnimatedText::_ready() {}

godot::PackedStringArray AnimatedText::_get_configuration_warnings() const {
  godot::PackedStringArray warnings;

  if (_texts.is_empty()) {
    warnings.push_back("texts is empty");
  }

  return warnings;
}

void AnimatedText::animate_text() {
  if (!_is_animating) {
    return;
  }

  switch (_state) {
  case State::Increment: {
    const int32_t new_visible_char = get_visible_characters() + 1;
    if (get_visible_ratio() < 1) {
      set_visible_characters(new_visible_char);
    } else {
      _is_animating = false;
      emit_signal(AnimatedText::SignalName::AnimationEnded);
    }
    break;
  }
  case State::Decrement: {
    const int32_t new_visible_char = get_visible_characters() - 1;
    if (new_visible_char >= 0) {
      set_visible_characters(new_visible_char);
    } else {
      _is_animating = false;
      emit_signal(AnimatedText::SignalName::AnimationEnded);
    }
    break;
  }
  }
}

void AnimatedText::start_animation() {
  if (_is_animating) {
    return;
  }

  if (_state == State::Decrement) {
    if (_printed_text_idx + 1 < _texts.size()) {
      ++_printed_text_idx;
    } else {
      _printed_text_idx = 0;
    }
  }

  update_text();

  switch (_state) {
  case State::Increment:
    _state = State::Decrement;
    break;
  case State::Decrement:
    _state = State::Increment;
    break;
  }

  _is_animating = true;
}

void AnimatedText::update_text() {
  const godot::PackedStringArray &texts = get_texts();
  if (texts.is_empty()) {
    if (!godot::Engine::get_singleton()->is_editor_hint()) {
      throw PropertyNotSetError("texts", "String[]");
    } else {
      return;
    }
  }
  if (_printed_text_idx >= texts.size()) {
    throw std::runtime_error(
        "Unexpected behavior : _printed_text_idx out of bound");
  }

  const godot::String text = texts[_printed_text_idx];
  set_text(text);
}
