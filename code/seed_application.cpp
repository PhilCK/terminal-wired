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
#include <bullet_wrapper/world.hpp>
#include <bullet_wrapper/rigidbody.hpp>
#include <bullet_wrapper/collider.hpp>
#include <memory>
#include <utils/timer.hpp>
#include <utils/logging.hpp>
#include <bindings/v_01/as_script_bindings.hpp>
#include <core/entity/entity.hpp>
#include <components/camera/camera_controller.hpp>
#include <components/transform/transform_controller.hpp>
#include <components/mesh/mesh_controller.hpp>
#include <components/mesh_renderer/mesh_renderer_controller.hpp>
#include <components/material/material_controller.hpp>


namespace
{
  const uint32_t screen_width = 1024;
  const uint32_t screen_height = 600;
  
  const core::entity ground_entity {1,1};
  const core::entity player_entity {2,2};
  const core::entity camera_entity {3,3};
}


int
main()
{
  // Platform logging.
  util::set_log_types(util::log_msg_types::errors | util::log_msg_types::warnings | util::log_msg_types::info);
  util::set_log_outputs(util::log_out::console | util::log_out::buffer);

  // Reg log callbacks before setup.
  sdl::set_error_callback([](const std::string &str){ util::log_info(str);});
  renderer::set_log_callback([](const uint32_t id, const std::string &str){ util::log_info(std::to_string(id) + " " + str); });
 
  // Init Script
  script_bindings::temp_as_binding_init();
  
  // Setup
  sdl::window window(screen_width, screen_height, false, "Wired");
  const sdl::ogl_context gl_context(window);
  sdl::input input;
  input.set_mouse_hold(true);
  
  // Init
  renderer::initialize();
  renderer::clear_color(0.2f, 0.3f, 0.3f);
  
  const std::string asset_path = util::get_resource_path() + "assets/";
  
  const renderer::vertex_format vert_fmt({
    renderer::attr_format_desc{"in_vs_position",      renderer::attr_type::FLOAT3},
    renderer::attr_format_desc{"in_vs_texture_coord", renderer::attr_type::FLOAT2},
    renderer::attr_format_desc{"in_vs_normal",        renderer::attr_type::FLOAT3},
  });
  assert(vert_fmt.is_valid());
  
  renderer::shader fullbright(renderer::shader_utils::get_shader_code_from_tagged_file(asset_path + "shaders/basic_fullbright.ogl"));
  assert(fullbright.is_valid());
  
  // Physics.
  bullet::world phys_world;
  
  auto cube_coll = bullet::create_capsule_collider();
  std::unique_ptr<bullet::rigidbody> cube_rb(new bullet::rigidbody(std::move(cube_coll),
                                                                   0, 50, 0,
                                                                   0.1,
                                                                   bullet::axis::y_axis));
  
  auto plane_coll = bullet::create_static_plane_collider();
  std::unique_ptr<bullet::rigidbody> ground_rb(new bullet::rigidbody(std::move(plane_coll), 0, 0, 0, 0));
  
  phys_world.add_rigidbody(std::move(cube_rb));
  phys_world.add_rigidbody(std::move(ground_rb));
  
  // Camera
  {
    math::transform cam_transform = math::transform_init(math::vec3_init(0, 4, 7), math::vec3_one(), math::quat());
    comp::transform_controller::set_transform(camera_entity, cam_transform);
    comp::camera set_camera(screen_width, screen_height, 0.1f, 1000.f, math::quart_tau() / 2);
    comp::camera_controller::set_camera(camera_entity, set_camera);
  }
  
  // Ground
  {
    math::transform ground_transform = math::transform_init(math::vec3_zero(), math::vec3_init(10, 1, 10), math::quat());
    comp::transform_controller::set_transform(ground_entity, ground_transform);
    
    comp::mesh ground_mesh = comp::load_from_file(asset_path + "models/unit_plane.obj");
    comp::mesh_controller::set_mesh(ground_entity, std::move(ground_mesh));
    
    comp::material ground_mat = comp::create_new(asset_path + "/textures/dev_grid_green_512.png");
    comp::material_controller::set(ground_entity, std::move(ground_mat));
  }
  
  // Player
  {
    math::transform player_transform = math::transform_init(math::vec3_init(0, 20, 0), math::vec3_one(), math::quat());
    comp::transform_controller::set_transform(player_entity, player_transform);
    
    auto coll = bullet::create_capsule_collider();
    bullet::rigidbody(std::move(coll), 0, 50, 0, 0.1, bullet::axis::y_axis);
    
    comp::mesh player_mesh = comp::load_from_file(asset_path + "models/unit_cube.obj");
    comp::mesh_controller::set_mesh(player_entity, std::move(player_mesh));
    
    comp::material ground_mat = comp::create_new(asset_path + "/textures/dev_grid_red_512.png");
    comp::material_controller::set(player_entity, std::move(ground_mat));
  }
  
  util::timer dt_timer;
  dt_timer.start();
  
  while(!window.wants_to_quit())
  {
    const float delta_time = dt_timer.split() / 1000.f;
  
    renderer::clear();
    renderer::reset();

    math::transform plane_transform = comp::transform_controller::get_transform(ground_entity);
    const math::mat4 p_world = math::transform_get_world_matrix(plane_transform);
    
    const math::mat4 world_rb = math::mat4_init_with_array(phys_world.get_rigidbody()->get_world_matrix());
    
    const auto current_camera = comp::camera_controller::get_camera(camera_entity);
    const auto proj = current_camera.get_proj_matrix();
    
    const auto cam_transform = comp::transform_controller::get_transform(camera_entity);
    const math::mat4 view = math::mat4_lookat(cam_transform.position, math::vec3_zero(), math::vec3_init(0, 1, 0));
    
    
    const math::mat4 wvp1 = math::mat4_multiply(p_world, view, proj);
    const math::mat4 wvp2 = math::mat4_multiply(world_rb, view, proj);
  
    phys_world.update_world(delta_time);
  
    // Render Scene
    {
      if(input.is_key_down(SDLK_w))
      {
        phys_world.get_rigidbody()->apply_local_force(0, 0, 1.f);
      }
      if(input.is_key_down(SDLK_s))
      {
        phys_world.get_rigidbody()->apply_local_force(0, 0, -1.f);
      }
      if(input.get_mouse_delta_x() != 0)
      {
        phys_world.get_rigidbody()->apply_local_torque(0, input.get_mouse_delta_x() * 0.1, 0);
      }
    
      renderer::reset();
      fullbright.set_raw_data("wvp", math::mat4_get_data(wvp1), 16 * sizeof(float));
      fullbright.set_texture("diffuse_map", comp::material_controller::get(ground_entity).map01);
      renderer::draw(fullbright, vert_fmt, comp::mesh_controller::get_mesh(ground_entity).vertex_info);
      
      renderer::reset();
      fullbright.set_raw_data("wvp", math::mat4_get_data(wvp2), 16 * sizeof(float));
      fullbright.set_texture("diffuse_map", comp::material_controller::get(player_entity).map01);
      renderer::draw(fullbright, vert_fmt, comp::mesh_controller::get_mesh(player_entity).vertex_info);
    }
    
    window.flip_buffer();
    sdl::message_pump();
  }

  return 0;
}