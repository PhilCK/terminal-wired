#include <systems/script/script_manager.hpp>
#include <systems/script/detail/meta_objects.hpp>
#include <systems/script/detail/chai_binding.hpp>
#include <systems/script/detail/chai_instances.hpp>
#include <utils/logging.hpp>
#include <chaiscript/ChaiScript.hpp>


namespace
{
  std::vector<Meta_object::Generic> objects; // temp.
}


namespace Sys {
namespace Script {


Script_manager::Script_manager()
{
}


bool
Script_manager::add_script(const Core::Entity entity, const std::string &code)
{
  auto ch_instance = Script_detail::Chai_instances::get_instance();
  
  assert(ch_instance.is_valid());
  if(!ch_instance.is_valid())
  {
    util::log_error("Script_manager - Failed to get a chai instance.");
    return false;
  }
  
  objects.push_back(Meta_object::Generic(Core::entity_as_uint(entity)));
  
  namespace chai_s = chaiscript;
  auto ch = ch_instance.get();
  
  ch->add(Script_detail::Chai_binding::get_binding_module());
  ch->add_global(chai_s::var(objects.back()), "seed"); // I think this will barf when ch is resued.
  ch->eval(code);
  
  return true;
}



} // ns
} // ns