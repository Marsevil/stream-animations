#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/shader_material.hpp>

#include "entities/animated_grid.hpp"
#include "entities/error.hpp"

using namespace entities;

void AnimatedGrid::_ready() {
  godot::Ref<godot::ShaderMaterial> shader(get_material());
  if (!shader.is_valid()) {
    if (godot::Engine::get_singleton()->is_editor_hint()) {
      return;
    } else {
      throw PropertyNotSetError("material", "ShaderMaterial");
    }
  }
}

void AnimatedGrid::_process(double delta) {
  if (!_animation_data) {
    return;
  }

  _animation_data->elapsed_time += delta;
  godot::Ref<godot::ShaderMaterial> shader(get_material());

  const double percent_anim = _animation_data->elapsed_time / _animation_time;
  double percent_show;
  switch (_animation_data->state) {
  case AnimationState::Appear:
    percent_show = percent_anim;
    break;
  case AnimationState::Disappear:
    percent_show = 1.0 - percent_anim;
    break;
  }
  shader->set_shader_parameter("percent_show", percent_show);

  if (percent_anim >= 1.0) {
    end_animation();
  }
}

void AnimatedGrid::start_animation() {
  if (_animation_data) {
    return;
  }

  godot::Ref<godot::ShaderMaterial> shader(get_material());
  const double show_percent = shader->get_shader_parameter(SHOW_PERCENT_PNAME);

  if (show_percent == 0.0) {
    _animation_data = {AnimationState::Appear, 0.0};
  } else {
    _animation_data = {AnimationState::Disappear, 0.0};
  }

  emit_signal(SignalName::AnimationStarted);
}

void AnimatedGrid::end_animation() {
  if (!_animation_data) {
    return;
  }

  godot::Ref<godot::ShaderMaterial> shader(get_material());
  switch (_animation_data->state) {
  case AnimationState::Appear:
    shader->set_shader_parameter(SHOW_PERCENT_PNAME, 1.0);
    break;
  case AnimationState::Disappear:
    shader->set_shader_parameter(SHOW_PERCENT_PNAME, 0.0);
    break;
  }

  _animation_data = std::nullopt;

  emit_signal(SignalName::AnimationEnded);
}
