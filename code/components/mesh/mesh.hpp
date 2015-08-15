#ifndef MESH_INCLUDED_5E1D36D7_6CEA_493B_A38A_6522493266F5
#define MESH_INCLUDED_5E1D36D7_6CEA_493B_A38A_6522493266F5


#include <simple_renderer/vertex_buffer.hpp>
#include <string>


namespace comp {


class mesh
{
public:

  mesh() {}

  mesh(mesh && other)
  {
    this->vertex_info = std::move(other.vertex_info);
  }
  
  mesh& operator=(mesh &&other)
  {
    this->vertex_info = std::move(other.vertex_info);
    
    return *this;
  }

  renderer::vertex_buffer vertex_info;
}; // class


mesh load_from_file(const std::string &file_name_and_path);


} // namespace


#endif // include guard