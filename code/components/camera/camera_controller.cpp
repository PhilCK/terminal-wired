#include "camera_component_controller.hpp"
#include <map>


namespace
{
  std::map<core::entity, comp::camera> cameras;
  std::map<core::entity, int> ints;
}


namespace comp {
namespace camera_controller {


bool
add_camera(const core::entity add_camera)
{
  camera new_cam = camera(800, 600, 0.1f, 1000.f, math::quart_tau());
  cameras.emplace(std::pair<core::entity, comp::camera>(add_camera, new_cam));
  
  return true;
}


void
set_camera(const core::entity set_camera_entity, const camera new_camera)
{
  if(cameras.count(set_camera_entity))
  {
    cameras.at(set_camera_entity) = new_camera;
  }
  else
  {
    cameras.emplace(std::pair<core::entity, comp::camera>(set_camera_entity, new_camera));
  }
  
}


camera
get_camera(const core::entity get_camera)
{
  
  return cameras.at(get_camera);
}


} // namespace
} // namespace