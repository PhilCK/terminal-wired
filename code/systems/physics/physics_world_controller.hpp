#ifndef PHYSICS_WORLD_CONTROLLER_INCLUDED_CEA51616_EE3C_4783_AD37_5E88BE708C54
#define PHYSICS_WORLD_CONTROLLER_INCLUDED_CEA51616_EE3C_4783_AD37_5E88BE708C54


#include <core/world/world.hpp>
#include <core/entity/entity.hpp>
#include <stdint.h>


namespace Physics_world {



struct Collision_event_data
{
  Core::Entity entity_a = Core::invalid_entity();
  Core::Entity entity_b = Core::invalid_entity();
};


void        create(const Core::World w);
void        destroy(const Core::World w);
void        think(const Core::World w);


} // ns


#endif // inc guard