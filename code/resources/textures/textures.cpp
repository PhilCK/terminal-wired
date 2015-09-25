#include <resources/textures/texture_resource.hpp>
#include <resources/textures/detail/texture_asset_manager.hpp>


namespace
{
  //Texture_resource::Detail::Texture_asset_manager tex_asset_mgr;
}


namespace Resource {
namespace Texture_controller {


void
initialize()
{
}


void
de_initialize()
{
}


Texture_asset
add_texture(const std::string &file)
{
  return Texture_asset();
  //return tex_asset_mgr.add_texture(file);
}


void
remove_texture(const uint32_t id)
{
}


} // ns
} // ns