#ifndef ENTITY_INCLUDED_DFC5F6F4_7B6C_464C_A1AC_58963A22E65A
#define ENTITY_INCLUDED_DFC5F6F4_7B6C_464C_A1AC_58963A22E65A


#include <stdint.h>


namespace Core {


struct Entity
{
  uint32_t type_id : 8;
  uint32_t instance_id : 24;
};


//! This is to allow dummy entities.
inline Entity invalid_entity() { return Entity{0,0}; }
  
// Check to see if two entities are exactly the same.
inline bool operator==(const Entity left, const Entity right)
{
  return ((left.type_id == right.type_id) && (left.instance_id == right.instance_id));
}


inline bool operator<(const Entity left, const Entity right)
{
  return ((left.type_id < right.type_id) && (left.instance_id < right.instance_id));
}



} // namespace



#endif // include guard