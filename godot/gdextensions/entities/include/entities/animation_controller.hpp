#ifndef __ENTITIES_ANIMATION_CONTROLLER_HPP
#define __ENTITIES_ANIMATION_CONTROLLER_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/node_path.hpp>

namespace entities {
class AnimationController : public godot::Node {
  GDCLASS(AnimationController, Node)

public:
  struct SignalName {
    static constexpr char *StartTextAnimation = (char *)"StartTextAnimation";
  };

  static void _bind_methods();

  AnimationController() = default;
  ~AnimationController() = default;
  AnimationController(AnimationController const &) = delete;

  void _ready() override;

  void restart_text_animation();
};
} // namespace entities

#endif
