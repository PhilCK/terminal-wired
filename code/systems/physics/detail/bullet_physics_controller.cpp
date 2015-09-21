#ifndef BULLET_PHYSICS_INCLUDED_65A7BE94_C58E_4CF3_8E61_F06E815E0BCB
#define BULLET_PHYSICS_INCLUDED_65A7BE94_C58E_4CF3_8E61_F06E815E0BCB


#include <systems/physics/physics_world_controller.hpp>
#include <systems/physics/rigidbody_controller.hpp>
#include <systems/physics/detail/physics_world/physics_world.hpp>
#include <core/time/time.hpp>
#include <core/event/event.hpp>
#include <vector>
#include <map>
#include <assert.h>


namespace
{
  std::map<Core::World, std::unique_ptr<Bullet::World> >             m_physics_worlds;
  std::map<Core::World, std::vector<std::unique_ptr<btRigidBody> > > m_rigidbodies;
}


namespace Rigidbody {


bool
add(const Core::World w, const Core::Entity e, const Construction_info &info)
{
  assert(m_physics_worlds.count(w) && m_physics_worlds.at(w));

  std::unique_ptr<btRigidBody> new_rb;

  return false;
}


bool
remove(const Core::World w, const Core::Entity e)
{
  return false;
}


void
apply_world_force(const Core::World w, const Core::Entity e, const math::vec3 force)
{
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