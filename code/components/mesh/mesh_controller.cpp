#include "mesh_controller.hpp"
#include <map>


namespace
{
  std::map<core::entity, comp::mesh> meshes;
}


namespace comp {
namespace mesh_controller {


void
add_mesh(const core::entity add_mesh)
{
  meshes.emplace(std::pair<core::entity, comp::mesh>(add_mesh, mesh()));
}


void
set_mesh(const core::entity set_mesh, mesh mesh_data)
{
  if(meshes.count(set_mesh))
  {
    meshes.at(set_mesh) = std::move(mesh_data);
  }
  else
  {
    meshes.emplace(std::pair<core::entity, comp::mesh>(set_mesh, std::move(mesh_data)));
  }
}


mesh&
get_mesh(const core::entity get_mesh)
{
  return meshes.at(get_mesh);
}


} // namespace
} // namespace