#ifndef CAMERA_COMPONENT_CONTROLLER_INCLUDED_250803C4_155A_4FFB_8731_9D28523A68AE
#define CAMERA_COMPONENT_CONTROLLER_INCLUDED_250803C4_155A_4FFB_8731_9D28523A68AE


#include <core/entity/entity.hpp>
#include "camera.hpp"


namespace comp {
namespace camera_controller {


bool    add_camera(const core::entity add_camera);
camera  get_camera(const core::entity get_camera);


} // namespace
} // namespace


#endif // include guard