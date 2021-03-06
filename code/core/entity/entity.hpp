#ifndef ENTITY_INCLUDED_DFC5F6F4_7B6C_464C_A1AC_58963A22E65A
#define ENTITY_INCLUDED_DFC5F6F4_7B6C_464C_A1AC_58963A22E65A


#include <stdint.h>


namespace Core {


struct Entity
{
  uint32_t type_id : 8;
  uint32_t instance_id : 24;
};


//! Creates an entity with a valid instance number, spawns an event.
Entity generate_entity(const uint8_t type_id);

//! Destroys an entity, core will no longer track it, spawn an event.
void destroy_entity(const Entity e);

//! Converts an entity type into a uint32_t type.
inline uint32_t entity_as_uint(const Core::Entity e) { return (e.type_id << 24) | e.instance_id; }

//! Converts a uint to an entity
inline Entity uint_as_entity(const uint32_t to_e) { return Entity{(to_e >> 24), (to_e >> 0 & 0xFFFF)}; }

//! This is to allow dummy entities.
inline Entity invalid_entity() { return Entity{0,0}; }
  
//! Check to see if two entities are exactly the same, type and instance.
inline bool operator==(const Entity left, const Entity right)
{
  return entity_as_uint(left) == entity_as_uint(right);
}

//! For use in containers etc.
inline bool operator<(const Entity left, const Entity right)
{
  return entity_as_uint(left) < entity_as_uint(right);
}


struct New_entity_event
{
  Entity e = invalid_entity();
};


struct Destroy_entity_event
{
  Entity e = invalid_entity();
};


} // namespace


#endif // include guard