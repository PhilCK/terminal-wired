 #include <systems/transform/transform_controller.hpp>
#include <utils/logging.hpp>
#include <core/event/event.hpp>
#include <core/core_event_ids.hpp>
#include <map>
#include <vector>


namespace
{
  struct World_transform
  {
    std::map<Core::Entity, math::transform> transforms;
  }; // class
  
  std::map<Core::World, World_transform> entity_transforms;
  
  bool
  transform_event_handler(const uint32_t id, const void *event_data)
  {
    switch(id)
    {
      case(Core::Event_id::entity_destroy):
      {
        const Core::Destroy_entity_event *data = static_cast<const Core::Destroy_entity_event*>(event_data);
        assert(data);
        
        Transform::remove(Core::World{1}, data->e);
        break;
      }
      default:
      {
        assert(false);
        util::log_error("Tranform got an event it doesn't know how to handle.");
      }
    }
    
    return false;
  }
}


namespace Transform {


bool
initialize()
{
  Core::Event::add_callback(Core::Event_id::entity_destroy, transform_event_handler);

  return true;
}


bool
add(const Core::World w, const Core::Entity e, const math::transform &t)
{
  // New world?
  if(!entity_transforms.count(w))
  {
    entity_transforms.insert(std::pair<Core::World, World_transform>(w, World_transform()));
  }
  // Check has transform
  else if(entity_transforms.at(w).transforms.count(e))
  {
    util::log_warning("Transform - Already have transform for entity");
    return false;
  }
  
  entity_transforms.at(w).transforms.insert(
    std::pair<Core::Entity, math::transform>(e, t)
  );
  
  return true;
}


bool
remove(const Core::World w, const Core::Entity e)
{
  // New world?
  if(!entity_transforms.count(w))
  {
    util::log_error("Transform - not found world to remove entity.");
    return false;
  }
  
  if(!entity_transforms.at(w).transforms.count(e))
  {
    util::log_error("Transform - not found entity to remove transform.");
    return false;
  }
  else
  {
    entity_transforms.at(w).transforms.erase(e);
  }
  
  return true;
}


bool
get(const Core::World w, const Core::Entity e, math::transform &t)
{
  // Has world?
  if(!entity_transforms.count(w))
  {
    util::log_error("Transform - not found world to get entity.");
    return false;
  }
  
  if(!entity_transforms.at(w).transforms.count(e))
  {
    util::log_error("Transform - not found entity to get transform.");
    return false;
  }
  else
  {
    t = entity_transforms.at(w).transforms.at(e);
  }
  
  return true;
}


bool
set(const Core::World w, const Core::Entity e, const math::transform &t)
{
  // New world?
  if(!entity_transforms.count(w))
  {
    util::log_error("Transform - not found world to set entity.");
    return false;
  }
  
  if(!entity_transforms.at(w).transforms.count(e))
  {
    util::log_error("Transform - not found entity to set transform.");
    return false;
  }
  else
  {
    entity_transforms.at(w).transforms.at(e) = t;
  }

  return true;
}


} // ns