#ifndef CAMERA_COMPONENT_CONTROLLER_INCLUDED_250803C4_155A_4FFB_8731_9D28523A68AE
#define CAMERA_COMPONENT_CONTROLLER_INCLUDED_250803C4_155A_4FFB_8731_9D28523A68AE


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include "camera.hpp"


namespace Component {


template<>
bool add<comp::camera>(const Core::Entity e);


template<>
bool get<comp::camera>(const Core::Entity e, comp::camera &get_mesh);


template<>
bool set<comp::camera>(const Core::Entity e, const comp::camera &set);


} // namespace


#endif // include guard