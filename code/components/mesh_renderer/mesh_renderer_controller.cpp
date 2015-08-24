#include <components/mesh_renderer/mesh_renderer_controller.hpp>


namespace Component {


template<>
bool add<mesh_renderer>(const Core::Entity e)
{
  return false;
}


template<>
bool set<mesh_renderer>(const Core::Entity e, const mesh_renderer &component)
{
  return false;
}


template<>
bool get<mesh_renderer>(const Core::Entity e, mesh_renderer &component)
{
  return false;
}


} // ns