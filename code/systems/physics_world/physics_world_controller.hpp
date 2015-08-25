#ifndef PHYSICS_WORLD_CONTROLLER_INCLUDED_66BD1F83_8EBD_4B57_82F7_2DCA7616DE12
#define PHYSICS_WORLD_CONTROLLER_INCLUDED_66BD1F83_8EBD_4B57_82F7_2DCA7616DE12


#include <array>
#include "Rigid_body_data.hpp"


namespace Physics_world {


//uint32_t                    add_rigid_body(const Rigidbody::Rigidbody_data &data);
//uint32_t                    remove_rigid_body(uint32_t);
//Rigidbody::Rigidbody_data   get_rigid_body_data(uint32_t);
//bool                        update_rigid_body_data(uint32_t id, uint32_t data);

std::array<float, 3>        get_gravity();
void                        set_gravity(const std::array<float, 3> &set_gravity);


namespace detail {

int                         get_world();

} // ns


} // ns


#endif // inc guard