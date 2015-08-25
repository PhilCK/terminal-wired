#ifndef RIGID_BODY_CONTROLLER_INCLUDED_229DD022_CDFB_4295_8B0A_327EBF82CE60
#define RIGID_BODY_CONTROLLER_INCLUDED_229DD022_CDFB_4295_8B0A_327EBF82CE60


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include <bullet_wrapper/world.hpp>
#include <components/rigid_body/rigid_body_data.hpp>


namespace comp {
namespace rigid_body_controller {


void      add(const Core::Entity add_rigid_body);
void      set(const Core::Entity set_rigid_body, bullet::rigidbody new_rigid_body);
bullet::world &get_world();
void      update_world(const float dt);


} // namespace
} // namespace


namespace Component {


template<>
bool add<Rigidbody::Rigidbody_data>(const Core::Entity e);


template<>
bool get<Rigidbody::Rigidbody_data>(const Core::Entity e, Rigidbody::Rigidbody_data &get);


template<>
bool set<Rigidbody::Rigidbody_data>(const Core::Entity e, const Rigidbody::Rigidbody_data &set);



} // ns


#endif // include guard