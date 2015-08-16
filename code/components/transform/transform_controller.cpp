#include "transform_controller.hpp"
#include <map>


namespace
{
  std::map<Core::Entity, math::transform> transforms;
}


namespace Component {


template<>
bool
add<math::transform>(const Core::Entity e)
{
  transforms.emplace(std::pair<Core::Entity, math::transform>(e, math::transform()));
  
  return true;
}

template<>
bool
get<math::transform>(const Core::Entity e, math::transform &get_mesh)
{
  get_mesh = transforms.at(e);
  
  return true;
}


template<>
bool
set<math::transform>(const Core::Entity e, const math::transform &set)
{
  if(transforms.count(e))
  {
    
  }
  else
  {
    transforms.emplace(std::pair<Core::Entity, math::transform>(e, set));
  }
  
  return true;
}


} // namespace