#include <algorithm>
#include <random>

#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "entities/random_animator.hpp"

using namespace entities;
using namespace godot;

bool RandomAnimator::is_animatable(const Node *node) {
  const bool is_animatable =
      node->has_method(EXPECTED_FUNC) && node->has_signal(EXPECTED_SIGNAL);
  return is_animatable;
}

RandomAnimator::RandomAnimator() {
  connect("child_entered_tree", Callable(this, "_child_added"));
  connect("child_exiting_tree", Callable(this, "_child_removed"));
}

PackedStringArray RandomAnimator::_get_configuration_warnings() const {
  PackedStringArray warnings;

  if (_animatables.empty()) {
    warnings.push_back("No animatable child");
  }

  return warnings;
}

void RandomAnimator::_ready() {}

void RandomAnimator::start_animation() {
  if (_animatables.empty()) {
    UtilityFunctions::push_warning("No Animatable find in children");
    return;
  }
  if (_is_animating) {
    return;
  }

  std::default_random_engine eng;
  std::uniform_int_distribution<size_t> dist(0, _animatables.size());
  size_t animatable_idx = dist(eng);

  Node *const animatable = _animatables[animatable_idx];
  animatable->call(EXPECTED_FUNC);
  _is_animating = animatable;
}

void RandomAnimator::_child_added(Node *node) {
  bool const is_animatable = this->is_animatable(node);
  bool const already_known = std::find(_animatables.begin(), _animatables.end(),
                                       node) != _animatables.end();
  if (is_animatable && !already_known) {
    _animatables.push_back(node);
    node->connect(EXPECTED_SIGNAL, Callable(this, "_animation_ended"));
  }
  update_configuration_warnings();
}

void RandomAnimator::_child_removed(Node *node) {
  std::vector<Node *>::iterator pos =
      std::find(_animatables.begin(), _animatables.end(), node);
  if (pos != _animatables.end()) {
    _animatables.erase(pos);
  }
  if (node == _is_animating) {
    _is_animating = nullptr;
  }
  update_configuration_warnings();
}

void RandomAnimator::_animation_ended() {
  _is_animating = nullptr;
  emit_signal(SignalName::AnimationEnded);
}
