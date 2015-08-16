#include "material_controller.hpp"
#include <map>


namespace
{
  std::map<Core::Entity, comp::material> materials;
}


namespace comp {
namespace material_controller {


void
add(const Core::Entity add_material)
{
  materials.emplace(std::pair<Core::Entity, comp::material>(add_material, comp::material()));
}


void
set(const Core::Entity set_material, comp::material add_material)
{
  if(materials.count(set_material))
  {
    materials.at(set_material) = std::move(add_material);
  }
  else
  {
    materials.emplace(std::pair<Core::Entity, comp::material>(set_material, std::move(add_material)));
  }
}


material&
get(const Core::Entity get_material)
{
  return materials.at(get_material);
}


} // namespace
} // namespace