#include <systems/script/script_engine.hpp>
#include "script_controller.hpp"
#include "script.hpp"
#include <map>


namespace
{
  std::map<Core::Entity, Script::Script_data> scripts;
}


namespace Script
{

void
reset(const Core::Entity e)
{
  scripts[e] = Script::Script_data(e);
}

void
on_throw(const Core::Entity e)
{
  scripts[e].call_thrown_hook();
}

}


namespace Component {


template<>
bool
add<Script::Script_data>(const Core::Entity e)
{
  scripts.emplace(std::pair<Core::Entity, Script::Script_data>(e, Script::Script_data(e)));

  return true;
}


template<>
bool
set<Script::Script_data>(const Core::Entity e, const Script::Script_data &component)
{
  scripts[e] = component;
  
  return true;
}


template<>
bool
get<Script::Script_data>(const Core::Entity e, Script::Script_data &component)
{
  component = scripts[e];

  return true;
}


} // namespace