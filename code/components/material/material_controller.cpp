#include "material_controller.hpp"
#include <map>


namespace
{
  std::map<core::entity, comp::material> materials;
}


namespace comp {
namespace material_controller {


void
add(const core::entity add_material)
{
  materials.emplace(std::pair<core::entity, comp::material>(add_material, comp::material()));
}


void
set(const core::entity set_material, comp::material add_material)
{
  if(materials.count(set_material))
  {
    materials.at(set_material) = std::move(add_material);
  }
  else
  {
    materials.emplace(std::pair<core::entity, comp::material>(set_material, std::move(add_material)));
  }
}


material&
get(const core::entity get_material)
{
  return materials.at(get_material);
}


} // namespace
} // namespace