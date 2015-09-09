#include <systems/script/script_controller.hpp>
#include <systems/script/detail/chai_instances.hpp>
#include <systems/script/detail/chai_binding.hpp>


namespace Sys {
namespace Script {


void
initialize()
{
  Script_detail::Chai_instances::initialize(/* instances */128);
  Script_detail::Chai_binding::initialize();
}


} // ns
} // ns