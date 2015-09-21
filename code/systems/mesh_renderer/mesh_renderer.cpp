/*
  Temp implimentation
  --
  The shader should be in the material or somewhere else.
*/

#include <systems/mesh_renderer/mesh_renderer.hpp>
#include <simple_renderer/lazy_include.hpp>
#include <systems/transform/transform_controller.hpp>
#include <components/material/material_controller.hpp>
#include <components/mesh/mesh_controller.hpp>
#include <utils/directory.hpp>
#include <assert.h>
#include <array>


namespace
{
  const renderer::vertex_format vert_fmt({
    renderer::attr_format_desc{"in_vs_position",      renderer::attr_type::FLOAT3},
    renderer::attr_format_desc{"in_vs_texture_coord", renderer::attr_type::FLOAT2},
    renderer::attr_format_desc{"in_vs_normal",        renderer::attr_type::FLOAT3},
  });
  
  renderer::shader fullbright(renderer::shader_utils::get_shader_code_from_tagged_file(util::get_resource_path() + "assets/shaders/basic_fullbright.ogl"));
  
  //renderer::shader fullbright(renderer::shader_utils::get_shader_code_from_tagged_file(util::get_resource_path() + "assets/shaders/dots.ogl"));
}


namespace Sys {
namespace Mesh_renderer {


void
initialize()
{
  assert(vert_fmt.is_valid());
  assert(fullbright.is_valid());
}


void
render(const Core::Entity entity, const math::mat4 &view_proj)
{
  renderer::reset();
  
  // Get wvp mat.
  math::mat4 wvp;
  {
    math::transform trans;
    assert(Transform::get(Core::World{1}, entity, trans));
    
    const math::mat4 world = math::transform_get_world_matrix(trans);
    
    wvp = math::mat4_multiply(world, view_proj);
    
    fullbright.set_raw_data("wvp", math::mat4_get_data(wvp), sizeof(math::mat4));
  }
  
  // Get material
  {
    comp::material mat;
    assert(Component::get(entity, mat));
    
    fullbright.set_texture("diffuse_map", mat.map01);
  }
  
  // Get Vertex buffer
  comp::mesh mesh;
  assert(Component::get(entity, mesh));
  
  // Draw
  renderer::draw(fullbright, vert_fmt, mesh.vertex_info);
  
}


} // ns
} // ns