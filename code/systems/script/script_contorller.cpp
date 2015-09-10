#include <systems/script/script_controller.hpp>
#include <systems/script/script_manager.hpp>
#include <systems/script/detail/chai_instances.hpp>
#include <systems/script/detail/chai_binding.hpp>


namespace
{
  Sys::Script::Script_manager script_mgr;
}


namespace Sys {
namespace Script {


void
initialize()
{
  Script_detail::Chai_instances::initialize(/* instances */128);
  Script_detail::Chai_binding::initialize();
}


Sys::Script::Script_manager&
get_current_script_mgr()
{
  return script_mgr;
}


bool
event_callback(const uint32_t id, void *data)
{
  a;dkfjajkf;akdfj
  // Adding callback for collision data.

  return false;
}


} // ns
} // ns