#include <systems/transform/transform_controller.hpp>
#include <utils/logging.hpp>
#include <map>
#include <vector>


namespace
{
  struct World_transform
  {
    std::map<Core::Entity, math::transform> transforms;
  }; // class
  
  std::map<Core::World, World_transform> entity_transforms;
}


namespace Transform {


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

  return false;
}


} // ns