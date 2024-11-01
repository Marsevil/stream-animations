#ifndef __ENTITIES_RANDOM_ANIMATOR_HPP
#define __ENTITIES_RANDOM_ANIMATOR_HPP

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>

namespace entities {

class RandomAnimator : public godot::Node {
  GDCLASS(RandomAnimator, godot::Node)

public:
  static constexpr char *EXPECTED_SIGNAL = (char *)"animation_ended";
  static constexpr char *EXPECTED_FUNC = (char *)"start_animation";
  struct SignalName {
    static constexpr char *AnimationEnded = (char *)"animation_ended";
  };

  static bool is_animatable(godot::Node const *node);

  RandomAnimator();
  RandomAnimator(const RandomAnimator &) = delete;
  ~RandomAnimator() = default;

  godot::PackedStringArray _get_configuration_warnings() const override;
  void _ready() override;

  void start_animation();

private:
  std::vector<godot::Node *> _animatables = {};
  godot::Node *_is_animating = nullptr;

  void _child_added(godot::Node *node);
  void _child_removed(godot::Node *node);
  void _animation_ended();

  static void _bind_methods() {
    ADD_SIGNAL(godot::MethodInfo(SignalName::AnimationEnded));

    godot::ClassDB::bind_method(godot::D_METHOD("start_animation"),
                                &RandomAnimator::start_animation);
    godot::ClassDB::bind_method(godot::D_METHOD("_child_added", "node"),
                                &RandomAnimator::_child_added);
    godot::ClassDB::bind_method(godot::D_METHOD("_child_removed", "node"),
                                &RandomAnimator::_child_removed);
    godot::ClassDB::bind_method(godot::D_METHOD("_animation_ended"),
                                &RandomAnimator::_animation_ended);
  }
};

} // namespace entities

#endif
