#ifndef MATERIAL_INCLUDED_6AD037D4_EB6D_4BBE_924D_1087F41CA463
#define MATERIAL_INCLUDED_6AD037D4_EB6D_4BBE_924D_1087F41CA463


#include <simple_renderer/texture.hpp>
#include <string>


namespace comp {


class material
{
public:

  material() {}

  material(material &&other) {
    this->map01 = std::move(other.map01);
  }
  
  material& operator=(material &&other)
  {
    this->map01 = std::move(other.map01);
    
    return *this;
  }

  renderer::texture map01;

}; // class


material create_new(const std::string &filename);


} // namespace


#endif // include gurard