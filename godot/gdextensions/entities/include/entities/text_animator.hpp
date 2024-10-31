#ifndef __ENTITIES_TEXT_ANIMATOR_HPP
#define __ENTITIES_TEXT_ANIMATOR_HPP

#include <cstddef>
#include <vector>

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>

#include "entities/animated_text.hpp"

namespace entities {

class TextAnimator : public godot::Control {
  GDCLASS(TextAnimator, Control)

public:
  struct SignalName {
    static constexpr char *AnimationEnd = (char *)"AnimationEnd";
  };

  TextAnimator() = default;
  TextAnimator(const TextAnimator &) = delete;
  ~TextAnimator() = default;

  void set_switch_delay(float value) { _switch_delay = value; }
  float get_switch_delay() { return _switch_delay; }

  void _ready() override;
  godot::PackedStringArray _get_configuration_warnings() const override;

  void switch_text();

private:
  double _switch_delay = 0.5;

  std::vector<AnimatedText *> _texts = {};
  size_t _current_text_idx = 0;
  godot::Timer *_switch_text_timer = nullptr;

  void _update_texts();
  void _show_text();
  void _text_animation_end(AnimatedText::AnimationState state);

  static void _bind_methods() {
    ADD_SIGNAL(godot::MethodInfo(TextAnimator::SignalName::AnimationEnd));

    godot::ClassDB::bind_method(godot::D_METHOD("set_switch_delay", "value"),
                                &TextAnimator::set_switch_delay);
    godot::ClassDB::bind_method(godot::D_METHOD("get_switch_delay"),
                                &TextAnimator::get_switch_delay);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "switch_delay"),
                 "set_switch_delay", "get_switch_delay");

    godot::ClassDB::bind_method(godot::D_METHOD("switch_text"),
                                &TextAnimator::switch_text);
    godot::ClassDB::bind_method(godot::D_METHOD("_text_animation_end"),
                                &TextAnimator::_text_animation_end);
    godot::ClassDB::bind_method(godot::D_METHOD("_show_text"),
                                &TextAnimator::_show_text);
  }
};

} // namespace entities

#endif
