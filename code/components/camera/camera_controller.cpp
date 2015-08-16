#include "camera_controller.hpp"
#include <map>


namespace
{
  std::map<Core::Entity, comp::camera> cameras;
  std::map<Core::Entity, int> ints;
}


namespace Component {

template<>
bool
add<comp::camera>(const Core::Entity add_camera)
{
  comp::camera new_cam = comp::camera(800, 600, 0.1f, 1000.f, math::quart_tau());
  cameras.emplace(std::pair<Core::Entity, comp::camera>(add_camera, new_cam));
  
  return true;
}


template<>
bool
set<comp::camera>(const Core::Entity set_camera_entity, const comp::camera &new_camera)
{
  if(cameras.count(set_camera_entity))
  {
    cameras.at(set_camera_entity) = new_camera;
  }
  else
  {
    cameras.emplace(std::pair<Core::Entity, comp::camera>(set_camera_entity, new_camera));
  }
  
  return true;
}


template<>
bool
get<comp::camera>(const Core::Entity get_camera, comp::camera &cam)
{
  cam = cameras.at(get_camera);
  
  return true;
}


} // namespace