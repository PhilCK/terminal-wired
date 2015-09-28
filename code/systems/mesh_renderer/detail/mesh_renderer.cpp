/*
  Temp implimentation
  --
  The shader should be in the material or somewhere else.
*/

#include <systems/mesh_renderer/detail/mesh_renderer.hpp>
#include <simple_renderer/lazy_include.hpp>
#include <systems/transform/transform_controller.hpp>
#include <systems/material/material_controller.hpp>
#include <components/mesh/mesh_controller.hpp>
#include <utils/directory.hpp>
#include <assert.h>
#include <array>


namespace
{
  renderer::vertex_format vert_fmt;
  
  renderer::shader fullbright;
  renderer::shader dir_light;
  
  //renderer::shader fullbright(renderer::shader_utils::get_shader_code_from_tagged_file(util::get_resource_path() + "assets/shaders/dots.ogl"));
}


namespace Mesh_renderer {
namespace Detail {


void
initialize()
{
  if(vert_fmt.is_valid())
  {
    return;
  }
  
  vert_fmt.load_format({
    renderer::attr_format_desc{"in_vs_position",      renderer::attr_type::FLOAT3},
    renderer::attr_format_desc{"in_vs_texture_coord", renderer::attr_type::FLOAT2},
    renderer::attr_format_desc{"in_vs_normal",        renderer::attr_type::FLOAT3},
  });

  fullbright.load_shader(renderer::shader_utils::get_shader_code_from_tagged_file(util::get_resource_path() + "assets/shaders/basic_fullbright.ogl"));
  dir_light.load_shader(renderer::shader_utils::get_shader_code_from_tagged_file(util::get_resource_path() + "assets/shaders/dir_light.ogl"));
  
  
  assert(vert_fmt.is_valid());
  assert(fullbright.is_valid());
  assert(dir_light.is_valid());
}


void
render(const Core::Entity entity, const math::mat4 &view, const math::mat4 &proj)
{
  renderer::reset();
  
  // Fullbright
  
//  // Get wvp mat.
//  math::mat4 wvp;
//  {
//    math::transform trans;
//    assert(Transform::get(Core::World{1}, entity, trans));
//    
//    const math::mat4 world = math::transform_get_world_matrix(trans);
//    
//    wvp = math::mat4_multiply(world, view, proj);
//    
//    fullbright.set_raw_data("wvp", math::mat4_get_data(wvp), sizeof(math::mat4));
//  }
//  
//  // Get material
//  {
//    comp::material mat;
//    assert(Component::get(entity, mat));
//    
//    fullbright.set_texture("diffuse_map", mat.map01);
//  }
//  
//  // Get Vertex buffer
//  comp::mesh mesh;
//  assert(Component::get(entity, mesh));
//  
//  // Draw
//  renderer::draw(fullbright, vert_fmt, mesh.vertex_info);

  // Basic fwd light
  
    // Get wvp mat.
  {
    math::transform trans;
    assert(Transform::get(Core::World{1}, entity, trans));
    
    const math::mat4 world = math::transform_get_world_matrix(trans);
    
    dir_light.set_raw_data("worldMat", math::mat4_get_data(world), sizeof(math::mat4));
    dir_light.set_raw_data("viewMat", math::mat4_get_data(view), sizeof(math::mat4));
    dir_light.set_raw_data("projMat", math::mat4_get_data(proj), sizeof(math::mat4));
  }
  
  // Get material
  {
   
    auto material = Material_controller::get_material(entity);
    
    if(material.details && material.details->map.is_valid())
    {
      dir_light.set_texture("diffuseTex", material.details->map);
    }
  }
  
  // Lighting info
  {
    std::array<float, 3> color = {1,1,1};
    dir_light.set_raw_data("gDirectionalLight.Base.Color", &color[0], sizeof(color));
    
    float thing = 0.7f;
    dir_light.set_raw_data("gDirectionalLight.Base.AmbientIntensity", &thing, sizeof(float));
    
    thing = 1.3f;
    dir_light.set_raw_data("gDirectionalLight.Base.DiffuseIntensity", &thing, sizeof(float));
    
    std::array<float, 3> dir {0.57735, -0.57735, 0.57735};
    dir_light.set_raw_data("gDirectionalLight.Direction", &dir[0], sizeof(dir));
  }
  
  // Get Vertex buffer
  comp::mesh mesh;
  assert(Component::get(entity, mesh));
  
  // Draw
  renderer::draw(dir_light, vert_fmt, mesh.vertex_info);
  
}


} // ns
} // ns