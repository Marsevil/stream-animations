# Entities GDExtension

## Build

1. Generate godot API file
  > `<path-to-godot> --dump-extension-api`
2. Generate cmake project
  > - Release : `cmake -D CMAKE_BUILD_TYPE=RELEASE -D GODOT_CUSTOM_API_FILE "$PWD/extension_api.json" -B target/release`
  > - Debug : `cmake -D CMAKE_BUILD_TYPE=DEBUG -D GODOT_ENABLE_HOT_RELOAD -D GODOT_CUSTOM_API_FILE "$PWD/extension_api.json" -B target/debug`
3. Build the library
  > `cmake --build target/<build_type>`
