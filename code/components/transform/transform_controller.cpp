#include "transform_component_controller.hpp"
#include <map>


namespace
{
  std::map<core::entity, math::transform> transforms;
}


namespace comp {
namespace transform_controller {


bool
add_transform(const core::entity add_transform)
{
  transforms.emplace(std::pair<core::entity, math::transform>(add_transform, math::transform()));
  
  return true;
}


math::transform
get_transform(const core::entity get_transform)
{
  return transforms.at(get_transform);
}


void
set_transform(const core::entity set_transform, const math::transform &new_transform)
{
  if(transforms.count(set_transform))
  {
    
  }
  else
  {
    transforms.emplace(std::pair<core::entity, math::transform>(set_transform, new_transform));
  }
}


} // namespace
} // namespace