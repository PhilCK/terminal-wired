#include <systems/material/material_controller.hpp>
#include <resources/textures/detail/texture_asset_manager.hpp>
#include <map>


namespace
{
  std::map<Core::Entity, Resource::Texture_asset> textures;
  Texture_resource::Detail::Texture_asset_manager texture_mgr;
}


namespace Material_controller {


void
add_material(const Core::Entity e, const std::string &filename)
{
  auto texture = texture_mgr.add_texture(filename);
  textures.insert(std::pair<Core::Entity, Resource::Texture_asset>(e, texture));
}


void
remove_material(const Core::Entity e)
{
}


Resource::Texture_asset
get_material(const Core::Entity e)
{
  if(textures.count(e))
  {
    return textures.at(e);
  }
  
  // Error
  return Resource::Texture_asset();
}


} // ns