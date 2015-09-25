#ifndef TEXTURE_ASSET_MANAGER_INCLUDED_9994DD36_F6D0_4FD1_8ABE_02AA47F9A9E1
#define TEXTURE_ASSET_MANAGER_INCLUDED_9994DD36_F6D0_4FD1_8ABE_02AA47F9A9E1


#include <resources/textures/detail/texture_asset_manager.hpp>
#include <string>


namespace Texture_resource {
namespace Detail {


class Texture_asset_manager
{
public:

  explicit      Texture_asset_manager();
  
  void          add_texture(const std::string &filename);
  void          remove_texture();
  
  void          flush_all_textures();
  
  
private:


  
  

}; // class


} // ns
} // ns


#endif // inc guard