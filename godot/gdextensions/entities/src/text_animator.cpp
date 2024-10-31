#include <cstddef>

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "entities/animated_text.hpp"
#include "entities/text_animator.hpp"

using namespace entities;

void TextAnimator::_update_texts() {
  this->_texts.clear();
  const godot::TypedArray<Node> children = this->get_children();
  for (size_t child_idx = 0; child_idx < children.size(); ++child_idx) {
    Node *const child = (Node *)(godot::Object *)(children[child_idx]);
    AnimatedText *const text = dynamic_cast<AnimatedText *>(child);
    if (!text) {
      continue;
    }

    this->_texts.push_back(text);
  }
}

void TextAnimator::_ready() {
  _update_texts();

  _switch_text_timer = memnew(godot::Timer);
  _switch_text_timer->set_one_shot(true);
  _switch_text_timer->set_wait_time(_switch_delay);
  _switch_text_timer->set_autostart(false);
  add_child(_switch_text_timer);

  for (AnimatedText *const text : _texts) {
    text->connect(AnimatedText::SignalName::AnimationAppearEnded,
                  godot::Callable(this, "_text_animation_end")
                      .bind(AnimatedText::AnimationState::Appear));
    text->connect(AnimatedText::SignalName::AnimationDisappearEnded,
                  godot::Callable(this, "_text_animation_end")
                      .bind(AnimatedText::AnimationState::Disappear));
  }

  _switch_text_timer->connect("timeout", godot::Callable(this, "_show_text"));
}

godot::PackedStringArray TextAnimator::_get_configuration_warnings() const {
  return godot::Control::_get_configuration_warnings();
}

void TextAnimator::switch_text() {
  AnimatedText *const text = _texts[_current_text_idx];
  text->start_disappear_animation();
}

void TextAnimator::_show_text() {
  AnimatedText *const text = _texts[_current_text_idx];
  text->start_appear_animation();
}

void TextAnimator::_text_animation_end(AnimatedText::AnimationState state) {
  switch (state) {
  case AnimatedText::AnimationState::Disappear:
    _current_text_idx = (_current_text_idx + 1) % _texts.size();
    _switch_text_timer->start();
    break;
  case AnimatedText::AnimationState::Appear:
    this->emit_signal(TextAnimator::SignalName::AnimationEnd);
    break;
  }
}
