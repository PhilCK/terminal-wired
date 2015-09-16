#include <systems/dot_renderer/dot_renderer.hpp>
#include <simple_renderer/lazy_include.hpp>
#include <components/transform/transform_controller.hpp>
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
  
  renderer::shader dot_shader(renderer::shader_utils::get_shader_code_from_tagged_file(util::get_resource_path() + "assets/shaders/dots.ogl"));
}



namespace Sys {
namespace Dot_renderer {


void
initialize()
{
  assert(vert_fmt.is_valid());
  assert(dot_shader.is_valid());
}


void
render(const Core::Entity entity, const math::mat4 &view_proj)
{
  renderer::reset();
  
  // Get wvp mat.
  math::mat4 wvp;
  {
    math::transform trans;
    assert(Component::get(entity, trans));
    
    const math::mat4 world = math::transform_get_world_matrix(trans);
    
    wvp = math::mat4_multiply(world, view_proj);
    
    dot_shader.set_raw_data("wvp", math::mat4_get_data(wvp), sizeof(math::mat4));
  }
  
  // Get Vertex buffer
  comp::mesh mesh;
  assert(Component::get(entity, mesh));
  
  // Draw
  renderer::draw(dot_shader, vert_fmt, mesh.vertex_info);
  
}



} // ns
} // ns