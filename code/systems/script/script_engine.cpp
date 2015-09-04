#include <systems/script/script_engine.hpp>
#include <utils/logging.hpp>
#include <utils/directory.hpp>


namespace
{
  chaiscript::ChaiScript chai({util::get_resource_path()});
  chaiscript::ModulePtr module;
}


namespace Sys {
namespace Script_engine {


void
initialize()
{
  module.reset(new chaiscript::Module());

  module->add(chaiscript::fun(&util::log_error),   "log_error");
  module->add(chaiscript::fun(&util::log_warning), "log_warning");
  module->add(chaiscript::fun(&util::log_info),    "log_info");
}


chaiscript::ChaiScript&
get_chai()
{
  return chai;
}


chaiscript::ModulePtr
get_module()
{
  return module;
}


} // ns
} // ns