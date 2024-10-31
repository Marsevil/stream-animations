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

#include "entities/animated_text.hpp"

using namespace entities;

AnimatedText::AnimatedText() { this->set_visible_characters(0); }

void AnimatedText::_ready() {}

void AnimatedText::_process(double delta) {
  if (!_animation_data) {
    return;
  }

  _animation_data->elapsed_time += delta;

  const double animation_perc = _animation_data->elapsed_time / _animation_time;
  double show_perc;
  switch (_animation_data->state) {
  case AnimationState::Appear:
    show_perc = animation_perc;
    break;
  case AnimationState::Disappear:
    show_perc = 1.0 - animation_perc;
    break;
  }

  set_visible_ratio(show_perc);

  if (animation_perc >= 1.0) {
    _end_animation();
  }
}

void AnimatedText::start_appear_animation() {
  set_visible_ratio(0.0);
  _animation_data = {AnimationState::Appear};
  emit_signal(SignalName::AnimationAppearStarted);
}

void AnimatedText::start_disappear_animation() {
  set_visible_ratio(1.0);
  _animation_data = {AnimationState::Disappear};
  emit_signal(SignalName::AnimationDisappearStarted);
}

void AnimatedText::_end_animation() {
  if (!_animation_data) {
    return;
  }

  const AnimationState animation_state = _animation_data->state;
  _animation_data = std::nullopt;

  switch (animation_state) {
  case AnimationState::Appear:
    set_visible_ratio(1.0);
    emit_signal(SignalName::AnimationAppearEnded);
    break;
  case AnimationState::Disappear:
    set_visible_ratio(0.0);
    emit_signal(SignalName::AnimationDisappearEnded);
    break;
  }
}
