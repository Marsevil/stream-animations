set(SRCS
    gdextension.cpp
    animated_grid.cpp
    animated_text.cpp
    animation_controller.cpp
    text_animator.cpp
    test.cpp
)

add_library(${PROJECT_NAME} SHARED ${SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE ../include)
target_include_directories(${PROJECT_NAME} PRIVATE ${bibsgodot_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC godot::cpp)
