#include <systems/mesh_renderer/mesh_renderer_controller.hpp>
#include <systems/mesh_renderer/detail/mesh_renderer.hpp>
#include <core/world/world.hpp>
#include <core/event/event.hpp>
#include <core/core_event_ids.hpp>
#include <utils/logging.hpp>
#include <set>
#include <map>


namespace
{
  std::map<Core::World, std::set<Core::Entity>> entities;
  
  bool
  mesh_renderer_event_handler(const uint32_t id, const void *event_data)
  {
    switch(id)
    {
      case(Core::Event_id::entity_destroy):
      {
        const Core::Destroy_entity_event *data = static_cast<const Core::Destroy_entity_event*>(event_data);
        Mesh_renderer::remove(Core::World{1}, data->e);
      }
      
      default:
      {
        util::log_warning("Mesh renderer recived an event it doesn't know how to deal with.");
      }
    }
  
    return false;
  }
} // ns


namespace Mesh_renderer {


void
create_world(const Core::World w)
{
  Core::Event::add_callback(Core::Event_id::entity_destroy, mesh_renderer_event_handler);

  Detail::initialize();
  entities.insert(std::pair<Core::World, std::set<Core::Entity>>(w, {}));
}


void
destroy_world(const Core::World w)
{
  util::log_error("destroy world not impl");
}


void
add(const Core::World w, const Core::Entity e)
{
  entities.at(w).insert(e);
}


void
remove(const Core::World w, const Core::Entity e)
{
  entities.at(w).erase(e);
}


void
think(const Core::World w, const math::mat4 &view, const math::mat4 &proj)
{
  for(auto &e : entities.at(w))
  {
    Detail::render(e, view, proj);
  }
}


} // ns