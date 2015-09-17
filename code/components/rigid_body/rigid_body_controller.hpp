#ifndef RIGID_BODY_CONTROLLER_INCLUDED_229DD022_CDFB_4295_8B0A_327EBF82CE60
#define RIGID_BODY_CONTROLLER_INCLUDED_229DD022_CDFB_4295_8B0A_327EBF82CE60


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include <bullet_wrapper/world.hpp>
#include <components/rigid_body/rigid_body_data.hpp>
#include <math/vec/vec3.hpp>
#include <math/transform/transform.hpp>


namespace comp {
namespace rigid_body_controller {


void      update_world(const float dt);


} // namespace
} // namespace


namespace Rigidbody {


void        apply_local_force(const Core::Entity e, const math::vec3 dir);
void        apply_world_force(const Core::Entity e, const math::vec3 dir);
void        apply_local_torque(const Core::Entity e, const math::vec3 rot);
void        set_transform(const Core::Entity e, const math::transform &trans);
void        set_gravity(const Core::Entity e, const math::vec3 dir);
void        set_mass(const Core::Entity e, const float mass);
void        set_trigger(const Core::Entity e, const bool set_trigger);


} // ns


namespace Component {


template<>
bool add<Rigidbody::Rigidbody_data>(const Core::Entity e);


template<>
bool get<Rigidbody::Rigidbody_data>(const Core::Entity e, Rigidbody::Rigidbody_data &get);


template<>
bool set<Rigidbody::Rigidbody_data>(const Core::Entity e, const Rigidbody::Rigidbody_data &set);


} // ns


#endif // include guard