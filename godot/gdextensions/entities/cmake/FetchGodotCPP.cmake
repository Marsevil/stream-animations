include(FetchContent)

FetchContent_Declare(
    GodotCPP
    GIT_REPOSITORY https://github.com/godotengine/godot-cpp.git
    GIT_TAG godot-4.3-stable
)

FetchContent_MakeAvailable(GodotCPP)
