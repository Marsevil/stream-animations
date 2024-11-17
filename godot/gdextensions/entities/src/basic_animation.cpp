#include "entities/basic_animation.hpp"
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/signal.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using namespace entities;

BasicAnimation::BasicAnimation() {
  connect("child_entered_tree", {this, "_on_child_added"});
  connect("child_exiting_tree", {this, "_on_child_removed"});
}

PackedStringArray BasicAnimation::_get_configuration_warnings() const {
  PackedStringArray warns;

  if (!_player) {
    warns.push_back("Animation not found in child");
  }

  return warns;
}

void BasicAnimation::start_animation() {
  if (!_player) {
    return;
  }

  _player->play(ANIMATION_NAME);
  emit_signal(SignalName::AnimationStarted);
}

void BasicAnimation::_animation_ended(StringName animation_name) {
  emit_signal(SignalName::AnimationEnded);
}

void BasicAnimation::_on_child_added(Node *node) {
  if (_player) {
    return;
  }
  if (AnimationPlayer *player = dynamic_cast<AnimationPlayer *>(node)) {
    _player = player;
    _player->connect("animation_finished", {this, "_animation_ended"});
  }
  update_configuration_warnings();
}

void BasicAnimation::_on_child_removed(Node *node) {
  if (_player == node) {
    _player = nullptr;
  }
  update_configuration_warnings();
}
