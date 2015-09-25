#ifndef BULLET_PHYSICS_INCLUDED_65A7BE94_C58E_4CF3_8E61_F06E815E0BCB
#define BULLET_PHYSICS_INCLUDED_65A7BE94_C58E_4CF3_8E61_F06E815E0BCB


#include <systems/physics/physics_world_controller.hpp>
#include <systems/physics/rigidbody_controller.hpp>
#include <systems/physics/detail/physics_world/physics_world.hpp>
#include <systems/physics/detail/rigidbody/default_bullet_motion_state.hpp>
#include <systems/physics/detail/rigidbody/actor_bullet_motion_state.hpp>
#include <systems/physics/detail/rigidbody/bullet_to_gl_tranform.hpp>
#include <common/event_ids.hpp>
#include <core/event/event.hpp>
#include <core/core_event_ids.hpp>
#include <core/time/time.hpp>
#include <core/event/event.hpp>
#include <utils/logging.hpp>
#include <vector>
#include <map>
#include <assert.h>


namespace
{
  std::map<Core::World, std::unique_ptr<Bullet::World> > m_physics_worlds;
  
  struct Rb_data
  {
    Rb_data() = default;
    Rb_data(Rb_data&&) = default;
    Rb_data& operator=(Rb_data&&) = default;
  
    std::unique_ptr<btRigidBody>      rb;
    std::unique_ptr<btMotionState>    mt;
    std::unique_ptr<btCollisionShape> coll;
    bool collision_event = false;
  };
  
  using Rb_container = std::map<Core::Entity, std::unique_ptr<Rb_data>>;
  std::map<Core::World, Rb_container> m_rigidbodies;
  
  
  bool
  phy_event_controller(const uint32_t event_id, const void *event_data)
  {
    if(event_id == Core::Event_id::entity_destroy)
    {
      const Core::Destroy_entity_event *data = static_cast<const Core::Destroy_entity_event*>(event_data);
      const Core::Entity remove_e = data->e;
      
      Rigidbody::remove(Core::World{1}, remove_e);
    }
    
    return false;
  }
}


namespace Rigidbody {


bool
add(const Core::World w, const Core::Entity e, const Construction_info &info)
{
  assert(m_physics_worlds.count(w) && m_physics_worlds.at(w));
  
  std::unique_ptr<Rb_data> data(new Rb_data());
  
  // Misc
  {
    data->collision_event = info.collision_event;
  }
  
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
  
  // Set user ptr
  {
    const uint32_t id = (Core::entity_as_uint(e));
  
    std::size_t* ptr = nullptr;
    ptr = (std::size_t*)id;
  
    data->rb->setUserPointer(ptr);
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
  
  // Add rb to world
  {
    assert(m_physics_worlds.at(w));
    m_physics_worlds.at(w)->add_rigidbody(data->rb.get());
  }
  
  // Add rb to collection
  {
    if(!m_rigidbodies.count(w))
    {
      m_rigidbodies.insert(std::pair<Core::World, Rb_container>(w, Rb_container()));
    }
    
    m_rigidbodies.at(w).insert(std::pair<Core::Entity, std::unique_ptr<Rb_data>>(e, std::move(data)));
  }

  return true;
}


bool
remove(const Core::World w, const Core::Entity e)
{
  const auto &rb_data = m_rigidbodies.at(w).at(e);
  
  m_physics_worlds.at(w)->get_world()->removeRigidBody(rb_data->rb.get());
  m_rigidbodies.at(w).erase(e);

  return true;
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
  
    if(!m_rigidbodies.at(w).count(e))
    {
      util::log_error("Rigidbody - Entity does not exist.");
      return nullptr;
    }
    
    return m_rigidbodies.at(w).at(e).get();
  }
  
  inline btDynamicsWorld*
  get_world(const Core::World w)
  {
    if(!m_physics_worlds.count(w))
    {
      util::log_error("Rigidbody - World does not exist.");
      return nullptr;
    }
    
    return m_physics_worlds.at(w)->get_world();
  }
}


void
apply_world_force(const Core::World w, const Core::Entity e, const math::vec3 force)
{
  Rb_data *rb_data = get_data(w, e);
  
  if(!rb_data)
  {
    util::log_warning("Rigidbody controller can't find that entity. Maybe its already gone out of scope.");
    return;
  }
  
  const btVector3 rel_pos(0, 0, 0);
  const btVector3 bt_force(math::vec3_get_x(force), math::vec3_get_y(force), math::vec3_get_z(force));

  rb_data->rb->activate(true);
  rb_data->rb->applyForce(bt_force, rel_pos);
}


void
apply_local_force(const Core::World w, const Core::Entity e, const math::vec3 force)
{
  Rb_data *rb_data = get_data(w, e);
  assert(rb_data && rb_data->rb);

  const btVector3 rel_pos(0, 0, 0);
  const btVector3 bt_force(math::vec3_get_x(force), math::vec3_get_y(force), math::vec3_get_z(force));
  const btVector3 w_force = rb_data->rb->getWorldTransform().getBasis() * bt_force;
  
  rb_data->rb->activate(true);
  rb_data->rb->applyForce(w_force, rel_pos);
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
  Rb_data *rb_data = get_data(w, e);
  assert(rb_data && rb_data->rb && rb_data->mt);
  
  btDynamicsWorld *world = get_world(w);
  assert(world);
  
  btRigidBody *rb = rb_data->rb.get();
  btMotionState *mt = rb_data->mt.get();
  
  rb->activate(true);
  //world->removeRigidBody(rb);
  
  // Transforms
  const btTransform bt_transform = Bullet::Detail::gl_to_bullet(transform);
  btTransform curr_trans;
  
  mt->setWorldTransform(bt_transform);
  rb->setMotionState(mt);
  
 // rb->getMotionState()->getWorldTransform(curr_trans);
  
  // We want to try and save the force to apply after tranform.
  //auto old_lin = rb->getLinearVelocity();
  //auto diff = bt_transform.getRotation() * curr_trans.getRotation().inverse();
  //auto rot_lin = old_lin.rotate(diff.getAxis(), diff.getAngle());
  //rb->setLinearVelocity(rot_lin);
  
 // mt->setWorldTransform(bt_transform);
 // rb->setMotionState(mt);

//  world->addRigidBody(rb);
}


} // ns


namespace Physics_world {


void
create(const Core::World w)
{
  Core::Event::add_callback(Core::Event_id::entity_destroy, phy_event_controller);

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
      
      // Not everybody wants a callback :)
      if(!Core::entity_as_uint(Core::invalid_entity()) && m_rigidbodies.at(w).at(ent_a)->collision_event)
      {
        const std::size_t entb_id = (std::size_t)coll.second;
        const Core::Entity ent_b = Core::uint_as_entity(static_cast<uint32_t>(entb_id));
        
        // Get some data from the event queue.
        void* data_loc = Core::Event::add_event_to_queue(Common::Event_ids::physics_collision, sizeof(Collision_event_data));
        assert(data_loc);
        
        // Create event data.
        const Collision_event_data * evt = new(data_loc) Collision_event_data{ent_a, ent_b};
        assert(evt);
      }
    }
  }
}


} // ns


#endif // include guard