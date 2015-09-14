#include <components/actor/actor_controller.hpp>


namespace Component {


template<>
bool
add<Actor_component>(const Core::Entity e)
{
  return false;
}


template<>
bool
get<Actor_component>(const Core::Entity e, Actor_component &get)
{
  return false;
}


template<>
bool
set<Actor_component>(const Core::Entity e, const Actor_component &set)
{
  return false;
}



} // ns