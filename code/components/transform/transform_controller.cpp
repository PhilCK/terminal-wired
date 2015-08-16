#include "transform_controller.hpp"
#include <map>


namespace
{
  std::map<core::entity, math::transform> transforms;
}


namespace component {


template<>
bool
add<math::transform>(const core::entity e)
{
  transforms.emplace(std::pair<core::entity, math::transform>(e, math::transform()));
  
  return true;
}

template<>
bool
get<math::transform>(const core::entity e, math::transform &get_mesh)
{
  get_mesh = transforms.at(e);
  
  return true;
}


template<>
bool
set<math::transform>(const core::entity e, const math::transform &set)
{
  if(transforms.count(e))
  {
    
  }
  else
  {
    transforms.emplace(std::pair<core::entity, math::transform>(e, set));
  }
  
  return true;
}


} // namespace