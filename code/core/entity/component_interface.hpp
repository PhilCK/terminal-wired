#ifndef COMPONENT_INCLUDED_9FA3DDA0_81CC_485B_B2AA_29034E58BE25
#define COMPONENT_INCLUDED_9FA3DDA0_81CC_485B_B2AA_29034E58BE25


/*

  Component interface. for implimenting component types.

  This isn't enforced by the engine in any particular way.
  A component might want to add their own function to add aditional args for example.

  This isn't in the core namespace because its really just a helper.

*/


#include <core/entity/entity.hpp>
#include <utils/logging.hpp>


namespace Component {


//! Add component to the entity.
template<typename T>
bool add(const Core::Entity e)
{
  util::log_warning("component type has not defined 'add'");
  return false;
}


//! Set the value of an entity.
template<typename T>
bool set(const Core::Entity e, const T &component)
{
  util::log_warning("component type has not defined 'set'");
  return false;
}


//! Get the data of the component.
template<typename T>
bool get(const Core::Entity e, T &component)
{
  util::log_warning("component type has not defined 'get'");
  return false;
}


//! Remove component from this entity.
template<typename T>
bool remove(const Core::Entity e)
{
  util::log_warning("component type has not defined 'remove'");
  return false;
}


//! Check to see if it has component.
template<typename T>
bool has(const Core::Entity e)
{
  util::log_warning("component type has not defined 'add'");
  return false;
}


} // namespace


#endif // include guard