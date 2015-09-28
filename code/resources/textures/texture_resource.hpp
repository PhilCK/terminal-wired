#ifndef TEXTURE_RESOURCE_INCLUDED_102C4C5E_7DFB_4758_B935_5E0FFC685A76
#define TEXTURE_RESOURCE_INCLUDED_102C4C5E_7DFB_4758_B935_5E0FFC685A76


#include <memory>
#include <simple_renderer/texture.hpp>


namespace Resource {


struct Texture_detail
{
  renderer::texture map;
};


class Texture_asset
{
public:

  explicit          Texture_asset() {}
                    ~Texture_asset() {}
  
  
  std::shared_ptr<const Texture_detail> details;

};


} // ns


#endif // inc guard