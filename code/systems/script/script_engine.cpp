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


namespace
{
  std::map<uint32_t, std::unique_ptr<chaiscript::ChaiScript>> chai_instances;
  uint32_t chai_instance = 0;
}


uint32_t
add_chai_instance()
{
  chai_instances.emplace(std::pair<uint32_t, std::unique_ptr<chaiscript::ChaiScript> >(++chai_instance, std::unique_ptr<chaiscript::ChaiScript>(new chaiscript::ChaiScript({util::get_resource_path()}))));
  
  return chai_instance;
}


chaiscript::ChaiScript&
get_chai(const uint32_t i)
{
  return *chai_instances[i];
}


void
remove_instance(const uint32_t id)
{
  chai_instances.erase(id);
}


} // ns
} // ns