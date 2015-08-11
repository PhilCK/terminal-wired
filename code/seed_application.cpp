#include <SDL2/SDL.h>
#include <sdl_wrapper/sdl_lazy_include.hpp>
#include <simple_renderer/lazy_include.hpp>
#include <SOIL/SOIL.h>
#include <utils/directory.hpp>
#include <utils/obj_model_loader.hpp>
#include <iostream>
#include <string>
#include <assert.h>
#include <math/math.hpp>


namespace
{
  void debug_log(const std::string &log_msg)
  {
    std::cout << log_msg << std::endl;
  }
}


int
main()
{
  // Reg log callbacks before setup.
  sdl::set_error_callback([](const std::string &str){debug_log(str);});
  renderer::set_log_callback([](const uint32_t id, const std::string &str){ debug_log(std::to_string(id) + " " + str); });
  
  // Setup
  sdl::window window(1024, 600, false);
  const sdl::ogl_context gl_context(window);
  sdl::input input;

  // Init
  renderer::initialize();
  renderer::clear_color(0.2f, 0.3f, 0.3f);
  
  const std::string asset_path = util::get_resource_path() + "assets/";
  
  const std::string dev_texture_name = asset_path + "/textures/dev_grid_green_512.png";
  int32_t width, height;
  uint8_t* image1 = SOIL_load_image(dev_texture_name.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
  const renderer::texture dev_texture1(image1, width, height);
  assert(dev_texture1.is_valid());
  SOIL_free_image_data(image1);

  const std::string dev_texture_name2 = asset_path + "/textures/dev_grid_red_512.png";
  uint8_t* image2 = SOIL_load_image(dev_texture_name2.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
  const renderer::texture dev_texture2(image2, width, height);
  assert(dev_texture2.is_valid());
  SOIL_free_image_data(image2);
  
  const util::obj_model model = util::load_obj(asset_path + "models/unit_plane.obj");
  const util::gl_mesh mesh = util::convert_to_open_gl_mesh(model.meshes.front());
  const renderer::vertex_buffer plane_mesh(mesh.mesh_data);
  assert(plane_mesh.is_valid());

  const util::obj_model cube_model = util::load_obj(asset_path + "models/unit_cube.obj");
  const util::gl_mesh cmesh = util::convert_to_open_gl_mesh(cube_model.meshes.front());
  const renderer::vertex_buffer cube_mesh(cmesh.mesh_data);
  assert(cube_mesh.is_valid());

  const renderer::vertex_format vert_fmt({
    renderer::attr_format_desc{"in_vs_position",      renderer::attr_type::FLOAT3},
    renderer::attr_format_desc{"in_vs_texture_coord", renderer::attr_type::FLOAT2},
    renderer::attr_format_desc{"in_vs_normal",        renderer::attr_type::FLOAT3},
  });
  assert(vert_fmt.is_valid());
  
  renderer::shader fullbright(renderer::shader_utils::get_shader_code_from_tagged_file(asset_path + "shaders/basic_fullbright.ogl"));
  assert(fullbright.is_valid());
  
  while(!window.wants_to_quit())
  {
    renderer::clear();
    renderer::reset();
    
    const math::mat4 p_scale = math::mat4_scale(10.f, 1.f, 10.f);
    const math::mat4 rot     = math::mat4_id();
    const math::mat4 trans   = math::mat4_id();
    const math::mat4 p_world = math::mat4_multiply(p_scale, rot, trans);
    const math::mat4 c_world = math::mat4_multiply(math::mat4_id(), rot, trans);

    const math::mat4 proj = math::mat4_projection(800, 600, 0.1f, 1000.f, math::half_pi() / 2);
    const math::mat4 view = math::mat4_lookat(math::vec3_init(0, 4, 7), math::vec3_zero(), math::vec3_init(0, 1, 0));
    const math::mat4 wvp1 = math::mat4_multiply(p_world, view, proj);
    const math::mat4 wvp2 = math::mat4_multiply(c_world, view, proj);
  
    // Render Scene
    {
      renderer::reset();
      fullbright.set_raw_data("wvp", math::mat4_get_data(wvp1), 16 * sizeof(float));
      fullbright.set_texture("diffuse_map", dev_texture1);
      renderer::draw(fullbright, vert_fmt, plane_mesh);
      
      renderer::reset();
      fullbright.set_raw_data("wvp", math::mat4_get_data(wvp2), 16 * sizeof(float));
      fullbright.set_texture("diffuse_map", dev_texture2);
      renderer::draw(fullbright, vert_fmt, cube_mesh);
    }
    
    window.flip_buffer();
    sdl::message_pump();
    
  }

  return 0;
}