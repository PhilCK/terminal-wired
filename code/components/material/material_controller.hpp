#ifndef MATERIAL_CONTROLLER_INCLUDED_0B9D6F45_EA0D_46A6_86D5_F6D17EFDF596
#define MATERIAL_CONTROLLER_INCLUDED_0B9D6F45_EA0D_46A6_86D5_F6D17EFDF596


#include <core/entity/entity.hpp>
#include "material.hpp"


namespace comp {
namespace material_controller {


void        add(const core::entity add_material);
void        set(const core::entity set_material, comp::material add_material);
material&   get(const core::entity get_material);


} // namespace
} // namespace


#endif // include guard