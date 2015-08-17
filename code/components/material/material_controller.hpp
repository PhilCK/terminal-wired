#ifndef MATERIAL_CONTROLLER_INCLUDED_0B9D6F45_EA0D_46A6_86D5_F6D17EFDF596
#define MATERIAL_CONTROLLER_INCLUDED_0B9D6F45_EA0D_46A6_86D5_F6D17EFDF596


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include "material.hpp"


namespace Component {


template<>
bool add<comp::material>(const Core::Entity e);


template<>
bool set<comp::material>(const Core::Entity e, const comp::material &component);


template<>
bool get<comp::material>(const Core::Entity e, comp::material &component);


} // namespace


#endif // include guard