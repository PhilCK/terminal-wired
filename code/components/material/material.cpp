#include "material.hpp"
#include <SOIL/SOIL.h>
#include <assert.h>


namespace comp {


material
create_new(const std::string &filename)
{
  int width, height;
  uint8_t* image_data = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
  const renderer::texture tex(image_data, width, height);
  assert(tex.is_valid());
  
  material new_mat;
  new_mat.map01.load_data(image_data, width, height);
  
  SOIL_free_image_data(image_data);
  
  return new_mat;
}


} // namespace