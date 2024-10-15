#ifndef __ENTITIES_ANIMATED_GRID
#define __ENTITIES_ANIMATED_GRID

#include <godot_cpp/classes/mesh_instance2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <optional>

namespace entities {

class AnimatedGrid : public godot::MeshInstance2D {
  GDCLASS(AnimatedGrid, MeshInstance2D)

public:
  struct SignalName {
    static constexpr char *AnimationEnded = (char *)"AnimationEnded";
    static constexpr char *AnimationStarted = (char *)"AnimationStarted";
  };

  enum AnimationState { Appear, Disappear };

  struct AnimationData {
    AnimationState state;
    double elapsed_time = 0.0;
  };

  AnimatedGrid() = default;
  ~AnimatedGrid() = default;
  AnimatedGrid(const AnimatedGrid &) = delete;

  void _ready() override;
  void _process(double delta) override;

  inline void set_animation_time(double value) { _animation_time = value; }
  inline double get_animation_time() const { return _animation_time; }

  void start_animation();
  void end_animation();

private:
  std::optional<AnimationData> _animation_data = std::nullopt;
  /// Animation time in second
  double _animation_time = 1.0;

  static constexpr char *SHOW_PERCENT_PNAME = (char *)"show_percent";

  static void _bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("set_animation_time", "value"),
                                &AnimatedGrid::set_animation_time);
    godot::ClassDB::bind_method(godot::D_METHOD("get_animation_time"),
                                &AnimatedGrid::get_animation_time);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "animation_time"),
                 "set_animation_time", "get_animation_time");

    godot::ClassDB::bind_method(godot::D_METHOD("start_animation"),
                                &AnimatedGrid::start_animation);
    godot::ClassDB::bind_method(godot::D_METHOD("end_animation"),
                                &AnimatedGrid::end_animation);

    ADD_SIGNAL({SignalName::AnimationStarted});
    ADD_SIGNAL({SignalName::AnimationEnded});
  }
};

} // namespace entities

#endif // !__ENTITIES_ANIMATED_GRID
