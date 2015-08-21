#include <SDL2/SDL.h>
#include <systems/window/window.hpp>
#include <sdl_wrapper/sdl_lazy_include.hpp>
#include <simple_renderer/lazy_include.hpp>
#include <SOIL/SOIL.h>
#include <utils/directory.hpp>
#include <utils/obj_model_loader.hpp>
#include <iostream>
#include <string>
#include <assert.h>
#include <memory>
#include <math/math.hpp>
#include <bullet_wrapper/world.hpp>
#include <bullet_wrapper/rigidbody.hpp>
#include <bullet_wrapper/collider.hpp>
#include <utils/timer.hpp>
#include <utils/logging.hpp>
#include <bindings/v_01/as_script_bindings.hpp>
#include <core/entity/entity.hpp>
#include <components/camera/camera_controller.hpp>
#include <components/transform/transform_controller.hpp>
#include <components/mesh/mesh_controller.hpp>
#include <components/mesh_renderer/mesh_renderer_controller.hpp>
#include <components/material/material_controller.hpp>
#include <components/rigid_body/rigid_body_controller.hpp>
#include <systems/script/script_environment.hpp>
#include <systems/debug_line_renderer/debug_line_renderer.hpp>


namespace
{
  const Core::Entity ground_entity {1,1};
  const Core::Entity player_entity {2,2};
  const Core::Entity camera_entity {3,3};
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

  
  // Setup
  sys::window::initialize(1280, 600, false, "Wired");
  sdl::input input;
  input.set_mouse_hold(true);
  
  // Init
  renderer::initialize();
  renderer::clear_color(0.2f, 0.3f, 0.3f);
  
  Sys::Debug_line_renderer::initialize();
  
  assert(sys::script_env::initialize());
  script_bindings_v01::bind_api(sys::script_env::get_as_engine());
  
  sys::script_env::test_hook();
  
  const std::string asset_path = util::get_resource_path() + "assets/";
  
  const renderer::vertex_format vert_fmt({
    renderer::attr_format_desc{"in_vs_position",      renderer::attr_type::FLOAT3},
    renderer::attr_format_desc{"in_vs_texture_coord", renderer::attr_type::FLOAT2},
    renderer::attr_format_desc{"in_vs_normal",        renderer::attr_type::FLOAT3},
  });
  assert(vert_fmt.is_valid());
  
  renderer::shader fullbright(renderer::shader_utils::get_shader_code_from_tagged_file(asset_path + "shaders/basic_fullbright.ogl"));
  assert(fullbright.is_valid());
  
  // Camera
  {
    math::transform cam_transform = math::transform_init(math::vec3_init(0, 4, 7), math::vec3_one(), math::quat());
    Component::set(camera_entity, cam_transform);
    comp::camera set_camera(sys::window::get_width(), sys::window::get_height(), 0.1f, 1000.f, math::quart_tau() / 2);
    Component::set(camera_entity, set_camera);
  }
  
  // Ground
  {
    math::transform ground_transform = math::transform_init(math::vec3_zero(), math::vec3_init(10, 1, 10), math::quat());
    Component::set<math::transform>(ground_entity, ground_transform);
    
    auto plane_coll = bullet::create_static_plane_collider();
    bullet::rigidbody rb(std::move(plane_coll), 0, 0, 0, 0);
    comp::rigid_body_controller::set(ground_entity, std::move(rb));
    
    comp::mesh ground_mesh = comp::load_from_file(asset_path + "models/unit_plane.obj");
    Component::set<comp::mesh>(ground_entity, ground_mesh);
    
    comp::material ground_mat = comp::create_new(asset_path + "/textures/dev_grid_green_512.png");
    //comp::material_controller::set(ground_entity, std::move(ground_mat));
    Component::set(ground_entity, ground_mat);
    
    auto static_plane = bullet::create_static_plane_collider();
    bullet::rigidbody new_rigid_body(std::move(static_plane), 0, 0, 0, 0);
    comp::rigid_body_controller::set(ground_entity, std::move(new_rigid_body));
  }
  
  // Player
  {
    math::transform player_transform = math::transform_init(math::vec3_init(0, 20, 0), math::vec3_one(), math::quat());
    Component::set(player_entity, player_transform);
    
    auto coll = bullet::create_capsule_collider();
    bullet::rigidbody rb(std::move(coll), -2, 2, 0, 0.1, bullet::axis::y_axis);
    comp::rigid_body_controller::set(player_entity, std::move(rb));
    
    comp::mesh player_mesh = comp::load_from_file(asset_path + "models/unit_cube.obj");
    Component::set<comp::mesh>(player_entity, player_mesh);
    
    comp::material ground_mat = comp::create_new(asset_path + "/textures/dev_grid_red_512.png");
    //comp::material_controller::set(player_entity, std::move(ground_mat));
    Component::set(player_entity, ground_mat);
  }
  
  util::timer dt_timer;
  dt_timer.start();
  
  //while(!window.wants_to_quit())
  while(sys::window::is_open())
  {
    const float delta_time = dt_timer.split() / 1000.f;
  
    renderer::clear();
    renderer::reset();

    math::transform plane_transform;
    Component::get<math::transform>(ground_entity, plane_transform);
    
    const math::mat4 p_world = math::transform_get_world_matrix(plane_transform);
    const math::mat4 world_rb = math::mat4_init_with_array(comp::rigid_body_controller::test()->get_world_matrix());
    const math::transform from_rb = math::transform_init_from_world_matrix(world_rb);
    
    
    comp::camera current_camera;
    Component::get(camera_entity, current_camera);
    const auto proj = current_camera.get_proj_matrix();
    
    math::transform player_transform;
    Component::get(player_entity, player_transform);
    //const math::vec3 fwd_vec = math::quat_rotate_point(player_t, <#const math::vec3 point#>)
    
    math::transform cam_transform;
    Component::get<math::transform>(camera_entity, cam_transform);
    
    const math::mat4 view = math::mat4_lookat(cam_transform.position, math::vec3_zero(), math::vec3_init(0, 1, 0));
    const math::mat4 wvp1 = math::mat4_multiply(p_world, view, proj);
    const math::mat4 wvp2 = math::mat4_multiply(world_rb, view, proj);
    
    comp::rigid_body_controller::update_world(delta_time);
  
    // Render Scene
    {
      if(input.is_key_down(SDLK_w))
      {
        comp::rigid_body_controller::test()->apply_local_force(0, 0, 1.f);
      }
      if(input.is_key_down(SDLK_s))
      {
        comp::rigid_body_controller::test()->apply_local_force(0, 0, -1.f);
      }
      if(input.get_mouse_delta_x() != 0)
      {
        comp::rigid_body_controller::test()->apply_local_torque(0, input.get_mouse_delta_x() * 0.1, 0);
      }
    
      renderer::reset();
      fullbright.set_raw_data("wvp", math::mat4_get_data(wvp1), 16 * sizeof(float));
      
      comp::material ground_mat;
      Component::get<comp::material>(ground_entity, ground_mat);
      
      fullbright.set_texture("diffuse_map", ground_mat.map01);
      comp::mesh mesh;
      Component::get<comp::mesh>(ground_entity, mesh);
      renderer::draw(fullbright, vert_fmt, mesh.vertex_info);
      
      renderer::reset();
      
      
      fullbright.set_raw_data("wvp", math::mat4_get_data(wvp2), 16 * sizeof(float));
      
      comp::material player_mat;
      Component::get<comp::material>(player_entity, player_mat);
      
      fullbright.set_texture("diffuse_map", player_mat.map01);
      Component::get<comp::mesh>(player_entity, mesh);
      renderer::draw(fullbright, vert_fmt, mesh.vertex_info);
    }
    
    // Debug lines
    {
      {
        btVector3 Start(0,2,0);
        btVector3 End(5,2,0);
        btVector3 Normal;
        
        btCollisionWorld::AllHitsRayResultCallback RayCallback(Start, End);
        
        Sys::Debug_line_renderer::add_line({Start.x(), Start.y(), Start.z()}, {End.x(),End.y(),End.z()}, {1,0,1});

        // Perform raycast
        comp::rigid_body_controller::get_world().get_world()->rayTest(Start, End, RayCallback);

        if(RayCallback.hasHit())
        {
          auto cb = RayCallback.m_collisionObject;
          //End = RayCallback.m_hitPointWorld;
          //Normal = RayCallback.m_hitNormalWorld;
        }

        // Do some clever stuff here
      }
    
      comp::camera current_camera;
      Component::get(camera_entity, current_camera);
      const auto proj = current_camera.get_proj_matrix();
      
      math::transform cam_transform;
      Component::get<math::transform>(camera_entity, cam_transform);
    
      const math::mat4 world = math::mat4_id();
      const math::mat4 view  = math::mat4_lookat(cam_transform.position, math::vec3_zero(), math::vec3_init(0, 1, 0));
      
      const math::mat4 wvp = math::mat4_multiply(world, view, proj);
      auto wvp_data = math::mat4_to_array(wvp);
    
      Sys::Debug_line_renderer::render(wvp_data);
    }
    
    sys::window::think();
  }

  return 0;
}