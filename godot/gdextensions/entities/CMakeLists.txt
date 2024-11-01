cmake_minimum_required(VERSION 3.28)
project(entities)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    set(GODOT_ENABLE_HOT_RELOAD ON)
endif()

include(cmake/FetchGodotCPP.cmake)
include(cmake/FetchBiBSGodot.cmake)

add_subdirectory(src)
