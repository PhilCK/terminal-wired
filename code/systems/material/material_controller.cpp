#include <systems/material/material_controller.hpp>
#include <resources/textures/texture_resource.hpp>
#include <map>


namespace
{
  std::map<Core::Entity, Resource::Texture_asset> textures;
}


namespace Material_controller {


void
add(const Core::Entity e, const std::string &filename)
{
  
}


void
remove(const Core::Entity e)
{
}


void
get(const Core::Entity e)
{
}


} // ns