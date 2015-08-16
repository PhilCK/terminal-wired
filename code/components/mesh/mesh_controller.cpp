#include "mesh_controller.hpp"
#include <map>


namespace
{
  std::map<Core::Entity, comp::mesh> meshes;
}


namespace Component {

template<>
bool
add<comp::mesh>(const Core::Entity e)
{
  meshes.emplace(std::pair<Core::Entity, comp::mesh>(e, comp::mesh()));
  
  return true;
}


template<>
bool
get<comp::mesh>(const Core::Entity e, comp::mesh &get_mesh)
{
  get_mesh = meshes.at(e);
  
  return true;
}


template<>
bool
set<comp::mesh>(const Core::Entity e, const comp::mesh &set)
{
  if(meshes.count(e))
  {
    meshes.at(e) = std::move(set);
  }
  else
  {
    meshes.emplace(std::pair<Core::Entity, comp::mesh>(e, std::move(set)));
  }
  
  return true;
}


} // namespace