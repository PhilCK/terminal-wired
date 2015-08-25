#include <systems/physics_world/physics_world_controller.hpp>


namespace
{
  bullet::world phy_world;
}


namespace Physics_world {


std::array<float, 3>
get_gravity()
{
  return {1,2,3};
}


void
set_gravity(const std::array<float, 3> &set_gravity)
{
  
}


namespace detail {

bullet::world&
get_world()
{
  return phy_world;
}

}


} // ns