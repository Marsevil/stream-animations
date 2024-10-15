#ifndef __ENTITIES_ANIMATED_TEXT_HPP
#define __ENTITIES_ANIMATED_TEXT_HPP

#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/string.hpp>

namespace entities {
class AnimatedText : public godot::Label {
  GDCLASS(AnimatedText, Label)

public:
  struct SignalName {
    static constexpr char *AnimationEnded = (char *)"AnimationEnded";
  };
  enum State { Increment, Decrement };

  AnimatedText();
  ~AnimatedText() = default;
  AnimatedText(const AnimatedText &) = delete;

  void _ready() override;
  godot::PackedStringArray _get_configuration_warnings() const override;

  void animate_text();
  void start_animation();

  inline void set_texts(godot::PackedStringArray value) {
    _texts = std::move(value);
    update_configuration_warnings();
  }
  inline godot::PackedStringArray const &get_texts() const { return _texts; }

private:
  void update_text();

  godot::PackedStringArray _texts = {};

  State _state = State::Increment;
  bool _is_animating = false;
  uint32_t _printed_text_idx = 0;

  static void _bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("set_texts", "value"),
                                &AnimatedText::set_texts);
    godot::ClassDB::bind_method(godot::D_METHOD("get_texts"),
                                &AnimatedText::get_texts);

    godot::ClassDB::bind_method(godot::D_METHOD("animate_text"),
                                &AnimatedText::animate_text);
    godot::ClassDB::bind_method(godot::D_METHOD("start_animation"),
                                &AnimatedText::start_animation);

    ADD_PROPERTY(
        godot::PropertyInfo(godot::Variant::PACKED_STRING_ARRAY, "texts"),
        "set_texts", "get_texts");

    ADD_SIGNAL(godot::MethodInfo(AnimatedText::SignalName::AnimationEnded));
  }
};
} // namespace entities

#endif // __ENTITIES_ANIMATED_TEXT_HPP
