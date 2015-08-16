#include "mesh_controller.hpp"
#include <map>


namespace
{
  std::map<core::entity, comp::mesh> meshes;
}


namespace component {

template<>
bool
add<comp::mesh>(const core::entity e)
{
  meshes.emplace(std::pair<core::entity, comp::mesh>(e, comp::mesh()));
  
  return true;
}


template<>
bool
get<comp::mesh>(const core::entity e, comp::mesh &get_mesh)
{
  get_mesh = meshes.at(e);
  
  return true;
}


template<>
bool
set<comp::mesh>(const core::entity e, const comp::mesh &set)
{
  if(meshes.count(e))
  {
    meshes.at(e) = std::move(set);
  }
  else
  {
    meshes.emplace(std::pair<core::entity, comp::mesh>(e, std::move(set)));
  }
  
  return true;
}


} // namespace