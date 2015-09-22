#ifndef BULLET_PHYSICS_INCLUDED_65A7BE94_C58E_4CF3_8E61_F06E815E0BCB
#define BULLET_PHYSICS_INCLUDED_65A7BE94_C58E_4CF3_8E61_F06E815E0BCB


#include <systems/physics/physics_world_controller.hpp>
#include <systems/physics/rigidbody_controller.hpp>
#include <systems/physics/detail/physics_world/physics_world.hpp>
#include <systems/physics/detail/rigidbody/default_bullet_motion_state.hpp>
#include <systems/physics/detail/rigidbody/actor_bullet_motion_state.hpp>
#include <core/time/time.hpp>
#include <core/event/event.hpp>
#include <utils/logging.hpp>
#include <vector>
#include <map>
#include <assert.h>


namespace
{
  std::map<Core::World, std::unique_ptr<Bullet::World> >             m_physics_worlds;
  
  struct Rb_data
  {
    Rb_data(Rb_data&&) = default;
    Rb_data& operator=(Rb_data&&) = default;
  
    std::unique_ptr<btRigidBody>      rb;
    std::unique_ptr<btMotionState>    mt;
    std::unique_ptr<btCollisionShape> coll;
  };
  
  std::map<Core::World, std::vector<std::unique_ptr<Rb_data>> > m_rigidbodies;
}


namespace Rigidbody {


bool
add(const Core::World w, const Core::Entity e, const Construction_info &info)
{
  assert(m_physics_worlds.count(w) && m_physics_worlds.at(w));
  
  std::unique_ptr<Rb_data> data;
  
  // Build collider.
  {
    switch(info.unkown_collider.id)
    {
      case(Collision_shape_id::box):
        data->coll.reset(new btBoxShape(btVector3(info.box_collider.x_extents, info.box_collider.y_extents, info.box_collider.z_extents)));
      break;
      
      case(Collision_shape_id::capsule):
        data->coll.reset(new btCapsuleShape(info.capsule_collider.radius, info.capsule_collider.height));
      break;
      
      case(Collision_shape_id::static_plane):
        data->coll.reset(new btStaticPlaneShape(btVector3(info.static_plane_collider.normal_x, info.static_plane_collider.normal_y, info.static_plane_collider.normal_z), info.static_plane_collider.offset));
      break;
      
      case(Collision_shape_id::unkown):
        assert(false);
        util::log_error("Rigidbody::add - need a collision type.");
        return false;
      break;
    }
  }
  
  // Build motion state.
  {
    switch(info.transform_hint)
    {
      case(Tranform_type::generic):
        data->mt.reset(new Bullet::Detail::Default_motion_state(w, e));
      break;
      
      case(Tranform_type::actor):
        data->mt.reset(new Bullet::Detail::Default_motion_state(w, e));
      break;
      
      default:
        assert(false);
        util::log_warning("Rigidbody::add unkown transform hint, applying generic.");
        data->mt.reset(new Bullet::Detail::Default_motion_state(w, e));
    }
  }
  
  // Create rb
  {
    btVector3 inertia(0, 0, 0);
    
    if(info.mass)
    {
      // TODO: Can I do this with just zero mass anyway?
      data->coll->calculateLocalInertia(info.mass, inertia);
    }

    btRigidBody::btRigidBodyConstructionInfo rigidbody_ci(info.mass, data->mt.get(), data->coll.get(), inertia);
    data->rb.reset(new btRigidBody(rigidbody_ci));
  }
  
  // Set axis
  {
    const btVector3 axis_movement((btScalar)(info.movement_axis >> 0 & 1),
                                  (btScalar)(info.movement_axis >> 1 & 1),
                                  (btScalar)(info.movement_axis >> 2 & 1));
    
    const btVector3 axis_rotation((btScalar)(info.rotation_axis >> 0 & 1),
                                  (btScalar)(info.rotation_axis >> 1 & 1),
                                  (btScalar)(info.rotation_axis >> 2 & 1));

    data->rb->setLinearFactor(axis_movement);
    data->rb->setAngularFactor(axis_rotation);
  }
  
  // Some general settings
  {
    data->rb->setDamping(0.9f, 0.9f);
    data->rb->setFriction(0.7f);
    data->rb->setRollingFriction(0.4f);
    data->rb->setRestitution(0.f);
  }
  
  if(!m_rigidbodies.count(w))
  {
    m_rigidbodies.insert(std::pair<Core::World, std::vector<std::unique_ptr<Rb_data> > >(w, {}));
  }
  
  // Add rb.
  m_rigidbodies.at(w).emplace_back(std::move(data));

  return true;
}


bool
remove(const Core::World w, const Core::Entity e)
{
  return false;
}


namespace
{
  inline Rb_data*
  get_data(const Core::World w, const Core::Entity e)
  {
    if(!m_rigidbodies.count(w))
    {
      util::log_error("Rigidbody - World does not exist.");
      return nullptr;
    }
  
    if(!m_rigidbodies.at(w).)
    Rb_data* data = nullptr;
  }
}


void
apply_world_force(const Core::World w, const Core::Entity e, const math::vec3 force)
{
 assert(rb);
    const btVector3 rel_pos(0, 0, 0);
    
    rb->activate(true);
    rb->applyForce(force, rel_pos);
}


void
apply_local_force(const Core::World w, const Core::Entity e, const math::vec3 force)
{
}


void
set_mass(const Core::World w, const Core::Entity e, const float set_mass)
{
}


float
get_mass(const Core::World w, const Core::Entity e)
{
  return 0.f;
}


void
set_move_axis(const Core::World w, const Core::Entity e, const uint32_t axis)
{
}


uint32_t
get_move_axis(const Core::World w, const Core::Entity e)
{
  return 0;
}


bool
can_move_on_x(const Core::World w, const Core::Entity e)
{
  return false;
}


bool
can_move_on_y(const Core::World w, const Core::Entity e)
{
  return false;
}


bool
can_move_on_z(const Core::World w, const Core::Entity e)
{
  return false;
}


void
set_rotation_axis(const Core::World w, const Core::Entity e, const uint32_t axis)
{
}


uint32_t
get_rotation_axis(const Core::World w, const Core::Entity e)
{
  return 0;
}


bool
can_rotate_on_x(const Core::World w, const Core::Entity e)
{
  return false;
}


bool
can_rotate_on_y(const Core::World w, const Core::Entity e)
{
  return false;
}


bool
can_rotate_on_z(const Core::World w, const Core::Entity e)
{
  return false;
}


void
set_trigger(const Core::World w, const Core::Entity e, const bool set_trigger)
{
}


bool
is_trigger(const Core::World w, const Core::Entity e)
{
  return false;
}

void
set_gravity(const Core::World w, const Core::Entity e, const math::vec3 force)
{
}


math::vec3
get_gravity(const Core::World w, const Core::Entity e)
{
  return math::vec3_zero();
}


void
set_transform(const Core::World w, const Core::Entity e, const math::transform &transform)
{
}


} // ns


namespace Physics_world {


void
create(const Core::World w)
{
  m_physics_worlds.insert(
    std::pair<Core::World, std::unique_ptr<Bullet::World> > (
      w, std::unique_ptr<Bullet::World>(new Bullet::World)
    )
  );
}


void
destroy(const Core::World w)
{
  m_physics_worlds.erase(w);
}


void
think(const Core::World w)
{
  // Todo: These should sub to scheduler.
  {
    m_physics_worlds.at(w)->think(Core::Time::get_delta_time());
    const auto collisions = m_physics_worlds.at(w)->get_collisions();
    
    // Send events.
    for(const auto &coll : collisions)
    {
      // Convert user pointers to entities.
      const std::size_t enta_id = (std::size_t)coll.first;
      const Core::Entity ent_a = Core::uint_as_entity(static_cast<uint32_t>(enta_id));

      const std::size_t entb_id = (std::size_t)coll.second;
      const Core::Entity ent_b = Core::uint_as_entity(static_cast<uint32_t>(entb_id));
      
      // Get some data from the event queue.
      void* data_loc = Core::Event::add_event_to_queue(collision_event_id, sizeof(Collision_event_data));
      assert(data_loc);
      
      // Create event data.
      const Collision_event_data * evt = new(data_loc) Collision_event_data{ent_a, ent_b};
      assert(evt);
    }
  }
}


} // ns


#endif // include guard