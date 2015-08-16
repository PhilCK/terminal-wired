/*

  Component interface. for implimenting component types.

  This isn't enforced by the engine in any particular way.
  A component might want to add their own function to add aditional args for example.

  This isn't in the core namespace because its really just a component helper.

*/

#ifndef COMPONENT_INCLUDED_9FA3DDA0_81CC_485B_B2AA_29034E58BE25
#define COMPONENT_INCLUDED_9FA3DDA0_81CC_485B_B2AA_29034E58BE25


#include <core/entity/entity.hpp>


namespace Component {


//! Add component to the entity.
template<typename T>
bool add(const Core::Entity e);


//! Set the value of an entity.
template<typename T>
bool set(const Core::Entity e, const T &component);


//! Get the data of the component.
template<typename T>
bool get(const Core::Entity e, T &component);


} // namespace


#endif // include guard