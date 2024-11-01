#ifndef __ENTITIES_ANIMATION_CONTROLLER_HPP
#define __ENTITIES_ANIMATION_CONTROLLER_HPP

#include <vector>

#include <BiBS.h>

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
  GDCLASS(AnimationController, godot::Node)
  BSCLASS;

public:
  typedef godot::TypedArray<godot::NodePath> TextPathArray;
  typedef std::vector<AnimatedText *> TextNodeArray;

  AnimationController() = default;
  ~AnimationController() = default;
  AnimationController(AnimationController const &) = delete;

  // Override
  godot::PackedStringArray _get_configuration_warnings() const override;
  void ready();

private:
  TextAnimator *_text = nullptr;
  BS_EXPORT(&AnimationController::_text, .name = "text");

  // Properties
  godot::Timer *_timer = nullptr;

  // Methods
  void _switch_text();
  BS_EXPORT(&AnimationController::_switch_text);
  void _text_animation_ended();
  BS_EXPORT(&AnimationController::_text_animation_ended);
};

} // namespace entities

#endif
