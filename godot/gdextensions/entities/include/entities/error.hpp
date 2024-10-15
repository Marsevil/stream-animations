#ifndef __ENTITIES_ERROR_HPP
#define __ENTITIES_ERROR_HPP

#include <format>
#include <stdexcept>

namespace entities {
class PropertyNotSetError : public std::runtime_error {
public:
  PropertyNotSetError(char const *property_name, char const *expect_type)
      : std::runtime_error(std::format("Property \"{}\" is not of type \"{}\"",
                                       property_name, expect_type)) {}
};
} // namespace entities

#endif
