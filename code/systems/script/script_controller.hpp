#ifndef SCRIPT_CONTROLLER_INCLUDED_68CB9F9E_0FBF_4551_AE23_A34E85C7467C
#define SCRIPT_CONTROLLER_INCLUDED_68CB9F9E_0FBF_4551_AE23_A34E85C7467C


#include <systems/script/detail/script_fwd.hpp>
#include <stdint.h>


namespace Sys {
namespace Script {


void                          initialize();
Sys::Script::Script_manager&  get_current_script_mgr();
bool                          event_callback(const uint32_t id, void *data);


} // ns
}


#endif // include guard