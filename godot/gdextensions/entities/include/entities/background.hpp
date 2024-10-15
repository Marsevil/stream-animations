#ifndef __ENTITIES_BACKGROUND_HPP
#define __ENTITIES_BACKGROUND_HPP

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>

namespace entities {
class Background : public godot::Sprite2D {
  GDCLASS(Background, Sprite2D)

public:
  Background() = default;
  ~Background() = default;
  Background(const Background &) = delete;

  static void _bind_methods();

  void _ready() override;
  void _process(double delta) override;

private:
  godot::Ref<godot::ShaderMaterial> m_shader = nullptr;
  double m_elapsed_time = 0.0;
};

} // namespace entities

#endif
