#ifndef MESH_CONTROLLER_INCLUDED_EE2B85B7_C634_4CF8_83C0_897F3EBD27D4
#define MESH_CONTROLLER_INCLUDED_EE2B85B7_C634_4CF8_83C0_897F3EBD27D4


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include "mesh.hpp"


//namespace component {
//
//bool
//
//}


namespace comp {
namespace mesh_controller {


void      add_mesh(const core::entity add_mesh);
void      set_mesh(const core::entity set_mesh, mesh mesh_data);
mesh&     get_mesh(const core::entity get_mesh);



} // namespace
} // namespace


#endif // include guard