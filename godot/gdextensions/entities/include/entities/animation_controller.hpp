#ifndef __ENTITIES_ANIMATION_CONTROLLER_HPP
#define __ENTITIES_ANIMATION_CONTROLLER_HPP

#include <vector>

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/typed_array.hpp>

#include "entities/animated_text.hpp"

namespace entities {

class AnimationController : public godot::Node {
  GDCLASS(AnimationController, Node)

public:
  typedef godot::TypedArray<godot::NodePath> TextPathArray;
  typedef std::vector<AnimatedText *> TextNodeArray;
  struct SignalName {
    static constexpr char *StartTextAnimation = (char *)"StartTextAnimation";
  };

  AnimationController() = default;
  ~AnimationController() = default;
  AnimationController(AnimationController const &) = delete;

  inline void set_text_paths(TextPathArray value) {
    _text_paths = value;
    update_configuration_warnings();
  }
  inline TextPathArray get_text_paths() { return _text_paths; }

  godot::PackedStringArray _get_configuration_warnings() const override;
  void _ready() override;

  void text_animation_ended(AnimatedText::AnimationState animation_state,
                            uint32_t text_idx);

private:
  void _start_text_animation();
  AnimatedText *_get_text(uint32_t text_idx) const;

  uint32_t _current_text_idx = 0;

  TextPathArray _text_paths = {};
  TextNodeArray _texts = {};

  static void _bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("set_texts", "value"),
                                &AnimationController::set_text_paths);
    godot::ClassDB::bind_method(godot::D_METHOD("get_texts"),
                                &AnimationController::get_text_paths);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::ARRAY, "texts",
                                     godot::PROPERTY_HINT_ARRAY_TYPE,
                                     "AnimatedText"),
                 "set_texts", "get_texts");

    godot::ClassDB::bind_method(godot::D_METHOD("text_animation_ended"),
                                &AnimationController::text_animation_ended);
  }
};

} // namespace entities

#endif
