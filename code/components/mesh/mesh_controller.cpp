#include "mesh_controller.hpp"
#include <map>


namespace
{
  std::map<core::entity, comp::mesh> meshes;
}


namespace comp {
namespace mesh_controller {


//void
//set_mesh(const core::entity set_mesh, mesh mesh_data)
//{
//
//}
//
//
//mesh&
//get_mesh(const core::entity get_mesh)
//{
//  return meshes.at(get_mesh);
//}


} // namespace
} // namespace



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
set<comp::mesh>(const core::entity e, comp::mesh &set)
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