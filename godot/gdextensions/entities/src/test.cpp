#include <godot_cpp/variant/utility_functions.hpp>

#include "entities/test.hpp"

void entities::TestNode::_ready() {
  godot::UtilityFunctions::print("I'm alive");
}

void entities::TestNode::_bind_methods() {}
