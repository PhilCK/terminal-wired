#ifndef OBJECT_FACTORY_INCLUDED_6841A4F4_FDE4_4237_99C8_B51F65778413
#define OBJECT_FACTORY_INCLUDED_6841A4F4_FDE4_4237_99C8_B51F65778413


#include <core/entity/entity.hpp>
#include <core/world/world.hpp>


namespace Object_factory {


Core::Entity    create_local_input_actor(const Core::World w);
Core::Entity    create_program_block(const Core::World w);
Core::Entity    create_camera(const Core::World w);
Core::Entity    create_non_physics_block(const Core::World w);
Core::Entity    create_static_ground(const Core::World w);


} // ns


#endif // inc guard