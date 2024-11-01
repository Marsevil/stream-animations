#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

#include "entities/animated_grid.hpp"
#include "entities/animated_text.hpp"
#include "entities/animation_controller.hpp"
#include "entities/random_animator.hpp"
#include "entities/test.hpp"
#include "entities/text_animator.hpp"

void init(godot::ModuleInitializationLevel init_level) {
  if (init_level !=
      godot::ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }

  GDREGISTER_CLASS(entities::TestNode);
  GDREGISTER_CLASS(entities::AnimationController);
  GDREGISTER_CLASS(entities::AnimatedGrid);
  GDREGISTER_CLASS(entities::AnimatedText);
  GDREGISTER_CLASS(entities::TextAnimator);
  GDREGISTER_CLASS(entities::RandomAnimator);
}

void deinit(godot::ModuleInitializationLevel init_level) {}

extern "C" {
GDExtensionBool GDE_EXPORT
extension_init(GDExtensionInterfaceGetProcAddress get_proc_address,
               const GDExtensionClassLibraryPtr library,
               GDExtensionInitialization *initialization) {
  godot::GDExtensionBinding::InitObject init_obj(get_proc_address, library,
                                                 initialization);

  init_obj.register_initializer(init);
  init_obj.register_terminator(deinit);
  init_obj.set_minimum_library_initialization_level(
      godot::MODULE_INITIALIZATION_LEVEL_SCENE);

  return init_obj.init();
}
}
