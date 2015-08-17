#include "material_controller.hpp"
#include <map>


namespace
{
  std::map<Core::Entity, comp::material> materials;
}


namespace Component {


template<>
bool
add<comp::material>(const Core::Entity e)
{
  materials.emplace(std::pair<Core::Entity, comp::material>(e, comp::material()));
  
  return true;
}


template<>
bool
set<comp::material>(const Core::Entity e, const comp::material &component)
{
  if(materials.count(e))
  {
    materials.at(e) = component;
  }
  else
  {
    materials.emplace(std::pair<Core::Entity, comp::material>(e, component));
  }
  
  return true;
}


template<>
bool
get<comp::material>(const Core::Entity e, comp::material &component)
{
  component = materials.at(e);
  
  return true;
}


} // namespace