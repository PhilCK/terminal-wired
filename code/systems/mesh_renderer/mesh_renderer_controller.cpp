#include <systems/mesh_renderer/mesh_renderer_controller.hpp>
#include <systems/mesh_renderer/detail/mesh_renderer.hpp>
#include <utils/logging.hpp>
#include <vector>
#include <map>


namespace
{
  std::map<Core::World, std::vector<Core::Entity>> entities;
} // ns


namespace Mesh_renderer {


void
create_world(const Core::World w)
{
  Detail::initialize();
  entities.insert(std::pair<Core::World, std::vector<Core::Entity>>(w, {}));
}


void
destroy_world(const Core::World w)
{
  util::log_error("destroy world not impl");
}


void
add(const Core::World w, const Core::Entity e)
{
  entities.at(w).push_back(e);
}


void
remove(const Core::World w, const Core::Entity e)
{
 util::log_error("remove ent not impl");
}


void
think(const Core::World w, const math::mat4 &view_proj)
{
  for(auto &e : entities.at(w))
  {
    Detail::render(e, view_proj);
  }
}


} // ns