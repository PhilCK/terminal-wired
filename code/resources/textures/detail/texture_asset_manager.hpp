#ifndef TEXTURE_ASSET_MANAGER_INCLUDED_9994DD36_F6D0_4FD1_8ABE_02AA47F9A9E1
#define TEXTURE_ASSET_MANAGER_INCLUDED_9994DD36_F6D0_4FD1_8ABE_02AA47F9A9E1


#include <resources/textures/texture_resource.hpp>
#include <vector>
#include <string>


namespace Texture_resource {
namespace Detail {


class Texture_asset_manager
{
public:

  explicit                    Texture_asset_manager();
  
  Resource::Texture_asset     add_texture(const std::string &filename);
  
  void                        flush_all_textures();
  
  
private:

  std::vector<Resource::Texture_asset> m_texture_assets;

}; // class


} // ns
} // ns


#endif // inc guard