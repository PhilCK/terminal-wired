#ifndef PHYSICS_WORLD_CONTROLLER_INCLUDED_66BD1F83_8EBD_4B57_82F7_2DCA7616DE12
#define PHYSICS_WORLD_CONTROLLER_INCLUDED_66BD1F83_8EBD_4B57_82F7_2DCA7616DE12


#include <core/entity/entity.hpp>
#include <array>
#include <bullet_wrapper/world.hpp>


namespace Sys {
namespace Physics_world {


const uint32_t collision_event_id = 123;

struct Collision_event
{
  Core::Entity entity_a = Core::invalid_entity();
  Core::Entity entity_b = Core::invalid_entity();
};


void                        initialize();
void                        update_world(const float dt);
std::array<float, 3>        get_gravity();
void                        set_gravity(const std::array<float, 3> &set_gravity);


/*
  Anything in the detail namespace is not part of the
  public interface.
*/
namespace detail {

bullet::world&              get_world(); //! Gets the underlying world resource.

} // ns

} // ns
} // ns


#endif // inc guard