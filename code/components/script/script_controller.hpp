#ifndef SCRIPT_CONTROLLER_INCLUDED_3F2B4133_DCB9_4FC2_968D_A6639817FE89
#define SCRIPT_CONTROLLER_INCLUDED_3F2B4133_DCB9_4FC2_968D_A6639817FE89


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include "script.hpp"


namespace Component {


template<>
bool add<comp::Script>(const Core::Entity e);


template<>
bool set<comp::Script>(const Core::Entity e, const comp::Script &component);


template<>
bool get<comp::Script>(const Core::Entity e, comp::Script &component);


} // namespace


#endif // include guard