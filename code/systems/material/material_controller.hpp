#ifndef MATERIAL_CONTROLLER_INCLUDED_693F6561_75CB_409D_B267_3D3082231F5B
#define MATERIAL_CONTROLLER_INCLUDED_693F6561_75CB_409D_B267_3D3082231F5B


#include <core/entity/entity.hpp>
#include <core/world/world.hpp>
#include <string>


namespace Material_controller {


void          add_material(const Core::Entity e, const std::string &filename);
void          remove_material(const Core::Entity e);


}


#endif // inc guard