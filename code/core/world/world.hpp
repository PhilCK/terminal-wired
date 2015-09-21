#ifndef WORLD_INCLUDED_7C5C8ED7_388E_43C0_93C2_B12DA9F1FC18
#define WORLD_INCLUDED_7C5C8ED7_388E_43C0_93C2_B12DA9F1FC18


#include <stdint.h>


namespace Core {


struct World
{
  uint32_t id = 0;
}; // struct


//! Check to see if two entities are exactly the same, type and instance.
inline bool operator==(const World left, const World right)
{
  return left.id == right.id;
}

//! For use in containers etc.
inline bool operator<(const World left, const World right)
{
  return left.id < right.id;
}


} // ns


#endif // include guard