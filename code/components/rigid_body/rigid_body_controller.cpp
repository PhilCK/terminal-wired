#include "rigid_body_controller.hpp"
#include <bullet_wrapper/world.hpp>
#include <map>


namespace
{
  std::map<core::entity, bullet::rigidbody> rigidbodies;
  bullet::world world;
}


namespace comp {
namespace rigid_body_controller {


void
add(const core::entity add_rigid_body)
{
  
}


void
set(const core::entity set_rigid_body, bullet::rigidbody new_rigid_body)
{
  //rigidbodies.emplace(std::pair<core::entity, bullet::rigidbody>(set_rigid_body, std::move(new_rigid_body)));
  world.add_rigidbody(std::make_unique<bullet::rigidbody>(std::move(new_rigid_body)));
}


bullet::rigidbody*
test()
{
  return world.get_rigidbody();
}



void
update_world(const float dt)
{
  world.update_world(dt);
}


} // namespace
} // namespace