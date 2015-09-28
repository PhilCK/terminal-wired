#include <resources/textures/detail/texture_asset_manager.hpp>
#include <resources/textures/texture_resource.hpp>
#include <utils/string_helpers.hpp>
#include <SOIL/SOIL.h>
#include <assert.h>


namespace Texture_resource {
namespace Detail {


Texture_asset_manager::Texture_asset_manager()
{
}

  
Resource::Texture_asset
Texture_asset_manager::add_texture(const std::string &filename)
{
  int32_t width, height;
  uint8_t* image_data = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
  const renderer::texture tex(image_data, width, height);
  assert(tex.is_valid());
  
  renderer::texture texture_asset(image_data, width, height);
  SOIL_free_image_data(image_data);

  Resource::Texture_asset asset;
  asset.details.reset(new Resource::Texture_detail{texture_asset});
  
  m_texture_assets.push_back(asset);
  
  return asset;
}
  

void
Texture_asset_manager::flush_all_textures()
{
  m_texture_assets.clear();
}


} // ns
} // ns