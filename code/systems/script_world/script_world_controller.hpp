#ifndef SCRIPT_CONTROLLER_INCLUDED_68CB9F9E_0FBF_4551_AE23_A34E85C7467C
#define SCRIPT_CONTROLLER_INCLUDED_68CB9F9E_0FBF_4551_AE23_A34E85C7467C


#include <systems/script_world/detail/script_fwd.hpp>
#include <core/world/world.hpp>
#include <core/entity/entity.hpp>
#include <string>
#include <stdint.h>


namespace Script {


void                          initialize();
Sys::Script::Script_manager&  get_current_script_mgr();
bool                          event_callback(const uint32_t id, const void *data);

bool    add(const Core::World w, const Core::Entity e, const std::string &code);
bool    remove(const Core::World w, const Core::Entity e);


} // ns


#endif // include guard