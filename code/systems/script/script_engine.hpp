#ifndef SCRIPT_ENGINE_INCLUDE_BA945647_F42A_4C42_AC0D_9DAEED35A933
#define SCRIPT_ENGINE_INCLUDE_BA945647_F42A_4C42_AC0D_9DAEED35A933


#include <chaiscript/chaiscript.hpp>


namespace Sys {
namespace Script_engine {


void                    initialize();
chaiscript::ChaiScript& get_chai();
chaiscript::ModulePtr   get_module();


uint32_t                  add_chai_instance();
chaiscript::ChaiScript&   get_chai(const uint32_t i);
void                      remove_instance(const uint32_t id);


} // ns
} // ns


#endif // inc guard