#include <stdexcept>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "entities/background.hpp"

using namespace entities;

void Background::_ready() {
  m_shader = get_material();

  if (m_shader == nullptr) {
    throw std::runtime_error("Shader should be set");
  }
}
void Background::_process(double delta) {
  if (godot::Engine::get_singleton()->is_editor_hint()) {
    return;
  }

  m_elapsed_time += delta;
  m_shader->set_shader_parameter("time", m_elapsed_time);
}

void Background::_bind_methods() {}
