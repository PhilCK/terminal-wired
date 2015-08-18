#include "script_controller.hpp"
#include <map>


namespace
{
  std::map<Core::Entity, comp::Script> scripts; // What is batch update on these???
}


namespace Script_utils
{

comp::Script
generate_script_data(const std::string &filename)
{
  return comp::Script();
}


void update()
{
  
}


} // ns


namespace Component {


template<>
bool add<comp::Script>(const Core::Entity e)
{
  return true;
}


template<>
bool set<comp::Script>(const Core::Entity e, const comp::Script &component)
{
  return true;
}


template<>
bool get<comp::Script>(const Core::Entity e, comp::Script &component)
{
  return true;
}


} // namespace