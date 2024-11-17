#ifndef __ENTITIES_BASIC_ANIMATION
#define __ENTITIES_BASIC_ANIMATION

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/string_name.hpp>

namespace entities {

class BasicAnimation : public godot::Node2D {
  GDCLASS(BasicAnimation, Node2D)

public:
  static constexpr char *ANIMATION_NAME = (char *)"default";

  struct SignalName {
    static constexpr char *AnimationEnded = (char *)"animation_ended";
    static constexpr char *AnimationStarted = (char *)"animation_started";
  };

  BasicAnimation();
  BasicAnimation(const BasicAnimation &) = delete;
  ~BasicAnimation() = default;

  godot::PackedStringArray _get_configuration_warnings() const override;

  void start_animation();

private:
  godot::AnimationPlayer *_player = nullptr;

  void _on_child_added(Node *node);
  void _on_child_removed(Node *node);
  void _animation_ended(godot::StringName animation_name);

  static void _bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("start_animation"),
                                &BasicAnimation::start_animation);
    godot::ClassDB::bind_method(godot::D_METHOD("_on_child_added", "node"),
                                &BasicAnimation::_on_child_added);
    godot::ClassDB::bind_method(godot::D_METHOD("_on_child_removed", "node"),
                                &BasicAnimation::_on_child_removed);
    godot::ClassDB::bind_method(
        godot::D_METHOD("_animation_ended", "animation_name"),
        &BasicAnimation::_animation_ended);

    ADD_SIGNAL({SignalName::AnimationStarted});
    ADD_SIGNAL({SignalName::AnimationEnded});
  }
};

} // namespace entities

#endif // !__ENTITIES_BASIC_ANIMATION
