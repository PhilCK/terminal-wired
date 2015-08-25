#ifndef PHYSICS_WORLD_CONTROLLER_INCLUDED_66BD1F83_8EBD_4B57_82F7_2DCA7616DE12
#define PHYSICS_WORLD_CONTROLLER_INCLUDED_66BD1F83_8EBD_4B57_82F7_2DCA7616DE12


#include <array>
#include <bullet_wrapper/world.hpp>


namespace Physics_world {


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


#endif // inc guard