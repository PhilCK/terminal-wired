#ifndef ACTOR_CONTROLLER_INCLUDED_8D50C454_0096_4090_8872_57046AB95A39
#define ACTOR_CONTROLLER_INCLUDED_8D50C454_0096_4090_8872_57046AB95A39


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>


namespace Component {


struct Actor_component
{
  enum class Actor_type { none, ai, input };
  
  Actor_type type = Actor_type::none;
};


template<>
bool add<Actor_component>(const Core::Entity e);


template<>
bool get<Actor_component>(const Core::Entity e, Actor_component &get);


template<>
bool set<Actor_component>(const Core::Entity e, const Actor_component &set);


} // ns


#endif // inc guard