#ifndef MESH_CONTROLLER_INCLUDED_EE2B85B7_C634_4CF8_83C0_897F3EBD27D4
#define MESH_CONTROLLER_INCLUDED_EE2B85B7_C634_4CF8_83C0_897F3EBD27D4


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include "mesh.hpp"


namespace Component {

template<>
bool add<comp::mesh>(const Core::Entity e);

template<>
bool get<comp::mesh>(const Core::Entity e, comp::mesh &get_mesh);


template<>
bool set<comp::mesh>(const Core::Entity e, const comp::mesh &set);


} // namespace


#endif // include guard