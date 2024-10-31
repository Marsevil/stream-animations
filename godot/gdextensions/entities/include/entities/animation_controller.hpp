#ifndef __ENTITIES_ANIMATION_CONTROLLER_HPP
#define __ENTITIES_ANIMATION_CONTROLLER_HPP

#include <vector>

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/node_path.hpp>
#include <godot_cpp/variant/typed_array.hpp>

#include "entities/animated_text.hpp"
#include "entities/text_animator.hpp"

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

  // Get / Set
  void set_text(TextAnimator *value) {
    _text = value;
    update_configuration_warnings();
  }
  TextAnimator *get_text() { return _text; }

  // Override
  godot::PackedStringArray _get_configuration_warnings() const override;
  void _ready() override;

private:
  // [Export]
  TextAnimator *_text = nullptr;

  // Properties
  godot::Timer *_timer = nullptr;

  // Methods
  void _switch_text();
  void _text_animation_ended();

  static void _bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("set_text", "value"),
                                &AnimationController::set_text);
    godot::ClassDB::bind_method(godot::D_METHOD("get_text"),
                                &AnimationController::get_text);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "text",
                                     godot::PROPERTY_HINT_NODE_TYPE,
                                     "TextAnimator"),
                 "set_text", "get_text");

    godot::ClassDB::bind_method(godot::D_METHOD("_switch_text"),
                                &AnimationController::_switch_text);
    godot::ClassDB::bind_method(godot::D_METHOD("_text_animation_ended"),
                                &AnimationController::_text_animation_ended);
  }
};

} // namespace entities

#endif
