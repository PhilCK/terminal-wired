#include "mesh.hpp"
#include <utils/obj_model_loader.hpp>

namespace comp {


mesh
load_from_file(const std::string &file_name_and_path)
{
  const util::obj_model model = util::load_obj(file_name_and_path);
  const util::gl_mesh mesh    = util::convert_to_open_gl_mesh(model.meshes.front());
  
  comp::mesh new_mesh_data;
  new_mesh_data.vertex_info.load_vertex_buffer(mesh.mesh_data);
  
  return new_mesh_data;
}


} // namespace