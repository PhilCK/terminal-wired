#ifndef RIGID_BODY_CONTROLLER_INCLUDED_229DD022_CDFB_4295_8B0A_327EBF82CE60
#define RIGID_BODY_CONTROLLER_INCLUDED_229DD022_CDFB_4295_8B0A_327EBF82CE60


#include <core/entity/entity.hpp>
#include <bullet_wrapper/world.hpp>
#include "rigid_body.hpp"


namespace comp {
namespace rigid_body_controller {


void      add(const Core::Entity add_rigid_body);
void      set(const Core::Entity set_rigid_body, bullet::rigidbody new_rigid_body);
bullet::world &get_world();
void      update_world(const float dt);

bullet::rigidbody* test();


} // namespace
} // namespace


#endif // include guard