#include <systems/window/window.hpp>
#include <sdl_wrapper/sdl_lazy_include.hpp>
#include <simple_renderer/lazy_include.hpp>
#include <SOIL/SOIL.h>
#include <utils/directory.hpp>
#include <string>
#include <assert.h>
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
#include <systems/mesh_renderer/mesh_renderer.hpp>
#include <systems/physics_world/physics_world_controller.hpp>


namespace
{
  const Core::Entity ground_entity {1,1};
  const Core::Entity player_entity {2,2};
  const Core::Entity camera_entity {3,3};
  const Core::Entity throw_entity  {4,4};
  const Core::Entity fwd_entity    {5,5};
  
  const math::vec3 world_up    = math::vec3_init(0.f, 1.f, 0.f);  // use common
  const math::vec3 world_fwd   = math::vec3_init(0.f, 0.f, -1.f); // use common
  const math::vec3 world_left  = math::vec3_init(1.f, 0.f, 0.f);  // use common
  
  sdl::input input;
}


void init_systems();
void init_entities();
void update_frame(const float dt);
void render_frame();


int
main()
{
  init_systems();
  init_entities();
  
  util::timer dt_timer;
  dt_timer.start();
  
  while(sys::window::is_open())
  {
    const float delta_time = dt_timer.split() * 0.001f;

    update_frame(delta_time);
    render_frame();
    // Render
  }

  return 0;
}


void
update_frame(const float dt)
{
  if(input.is_key_down(SDLK_w))
  {
    Rigidbody::apply_local_force(player_entity, math::vec3_init(0, 0, -1));
  }
  if(input.is_key_down(SDLK_s))
  {
    Rigidbody::apply_local_force(player_entity, math::vec3_init(0, 0, 1));
  }
  if(input.is_key_down(SDLK_a))
  {
    Rigidbody::apply_local_force(player_entity, math::vec3_init(-1, 0, 0));
  }
  if(input.is_key_down(SDLK_d))
  {
    Rigidbody::apply_local_force(player_entity, math::vec3_init(1, 0, 0));
  }
  if(input.get_mouse_delta_x() != 0)
  {
    Rigidbody::apply_local_torque(player_entity, math::vec3_init(0, input.get_mouse_delta_x() * 0.1f, 0));
  }
  if(input.is_key_down(SDLK_SPACE))
  {
    // Get player entity fwd vec.
    math::transform player_transform;
    assert(Component::get(player_entity, player_transform));
    
    const auto player_fwd = math::quat_rotate_point(player_transform.rotation, world_fwd);
    const auto throw_dir = math::vec3_add(player_fwd, math::vec3_init(0, 0.7, 0));
    const auto throw_scale = math::vec3_scale(throw_dir, 30000.f * dt);
    
    math::transform throw_transform;
    throw_transform.rotation = player_transform.rotation;
    throw_transform.position = math::vec3_add(player_transform.position, player_fwd);
    
    Rigidbody::set_transform(throw_entity, throw_transform);
    Rigidbody::apply_world_force(throw_entity, throw_scale);
  }
  
  // Move fwd entity
  {
    math::transform player_transform;
    assert(Component::get(player_entity, player_transform));

    const auto player_fwd = math::quat_rotate_point(player_transform.rotation, world_fwd);

    math::transform trans;
    assert(Component::get(fwd_entity, trans));

    trans.position = math::vec3_add(player_transform.position, player_fwd);
    assert(Component::set(fwd_entity, trans));
  }

  comp::rigid_body_controller::update_world(dt);
  Sys::Physics_world::update_world(dt);
  sys::window::think();
  
//  // ray test
//  {
//    btVector3 Start(0,2,0);
//    btVector3 End(5,2,0);
//    btVector3 Normal;
//    
//    btCollisionWorld::AllHitsRayResultCallback RayCallback(Start, End);
//    
//    Sys::Debug_line_renderer::add_line({Start.x(), Start.y(), Start.z()}, {End.x(),End.y(),End.z()}, {1,0,1});
//
//    // Perform raycast
//    comp::rigid_body_controller::get_world().get_world()->rayTest(Start, End, RayCallback);
//
//    if(RayCallback.hasHit())
//    {
//      auto cb = RayCallback.m_collisionObject;
//      //End = RayCallback.m_hitPointWorld;
//      //Normal = RayCallback.m_hitNormalWorld;
//    }
//
//    // Do some clever stuff here
//  }
}


void
render_frame()
{
  renderer::clear();
  renderer::reset();

  math::transform trans;
  assert(Component::get(player_entity, trans));
  
  const math::vec3 fwd = math::quat_rotate_point(trans.rotation, world_fwd);
  
  comp::camera current_camera;
  Component::get(camera_entity, current_camera);
  const auto proj = current_camera.get_proj_matrix();
  
  math::transform cam_transform;
  Component::get<math::transform>(camera_entity, cam_transform);
  
  //const math::mat4 view = math::mat4_lookat(cam_transform.position, math::vec3_zero(), math::vec3_init(0, 1, 0));
  const math::mat4 view = math::mat4_lookat(trans.position, math::vec3_add(trans.position, fwd), math::quat_rotate_point(trans.rotation, world_up));
  const math::mat4 view_proj = math::mat4_multiply(view, proj);

  // Render Scene
  {
    Sys::Mesh_renderer::render(ground_entity, view_proj);
    Sys::Mesh_renderer::render(player_entity, view_proj);
    Sys::Mesh_renderer::render(throw_entity, view_proj);
    Sys::Mesh_renderer::render(fwd_entity, view_proj);
  }
  
  // Debug lines
  {
    const math::vec3 fwd = math::quat_rotate_point(trans.rotation, world_fwd);
    const math::vec3 up  = math::quat_rotate_point(trans.rotation, world_up);
  
    comp::camera current_camera;
    Component::get(camera_entity, current_camera);
    const auto proj = current_camera.get_proj_matrix();
    
    math::transform cam_transform;
    Component::get<math::transform>(camera_entity, cam_transform);
  
    const math::mat4 world = math::mat4_id();
    
    //const math::mat4 view  = math::mat4_lookat(cam_transform.position, math::vec3_zero(), math::vec3_init(0, 1, 0));
    const math::mat4 view = math::mat4_lookat(trans.position, math::vec3_add(trans.position, fwd), up);
    
    const math::mat4 wvp = math::mat4_multiply(world, view, proj);
    auto wvp_data = math::mat4_to_array(wvp);
  
    Sys::Debug_line_renderer::render(wvp_data);
  }
}


void
init_entities()
{
  const std::string asset_path = util::get_resource_path() + "assets/";

  // Camera
  {
    math::transform cam_transform = math::transform_init(math::vec3_init(0, 4, 7), math::vec3_one(), math::quat());
    Component::set(camera_entity, cam_transform);
    comp::camera set_camera(sys::window::get_width(), sys::window::get_height(), 0.1f, 1000.f, math::quart_tau() / 2);
    Component::set(camera_entity, set_camera);
  }
  
  // Ground
  {
    math::transform ground_transform = math::transform_init(math::vec3_zero(), math::vec3_init(10, 0, 10), math::quat());
    Component::set<math::transform>(ground_entity, ground_transform);
    
    Rigidbody::Rigidbody_data rb_data;
    rb_data.mass = 0;
    rb_data.collider.type = Rigidbody::Collider_type::static_plane;
    rb_data.collider.static_plane_collider_args.normal_x = 0;
    rb_data.collider.static_plane_collider_args.normal_y = 0;
    rb_data.collider.static_plane_collider_args.normal_z = 0;
    rb_data.collider.static_plane_collider_args.offset   = 0;
    
    Component::set<Rigidbody::Rigidbody_data>(ground_entity, rb_data);
    
    comp::mesh ground_mesh = comp::load_from_file(asset_path + "models/unit_plane.obj");
    Component::set<comp::mesh>(ground_entity, ground_mesh);
    
    comp::material ground_mat = comp::create_new(asset_path + "/textures/dev_grid_green_512.png");
    Component::set(ground_entity, ground_mat);
  }
  
  // Player
  {
    math::transform player_transform = math::transform_init(math::vec3_init(0, 3, 0), math::vec3_one(), math::quat());
    Component::set(player_entity, player_transform);
  
    Rigidbody::Rigidbody_data rb_data;
    rb_data.mass = 0.1f;
    rb_data.collider.type = Rigidbody::Collider_type::capsule;
    
    Component::set<Rigidbody::Rigidbody_data>(player_entity, rb_data);
    
    comp::mesh player_mesh = comp::load_from_file(asset_path + "models/unit_cube.obj");
    Component::set<comp::mesh>(player_entity, player_mesh);
    
    comp::material ground_mat = comp::create_new(asset_path + "/textures/dev_grid_red_512.png");
    //comp::material_controller::set(player_entity, std::move(ground_mat));
    Component::set(player_entity, ground_mat);
  }
  
  // Throwable
  {
    math::transform trans = math::transform_init(math::vec3_init(2, 1, 0), math::vec3_one(), math::quat());
    Component::set(throw_entity, trans);
    
    //auto coll = bullet::create_capsule_collider();
    
    Rigidbody::Rigidbody_data rb_data;
    rb_data.mass = 3.f;
    rb_data.collider.type = Rigidbody::Collider_type::box;
    
    Component::set<Rigidbody::Rigidbody_data>(throw_entity, rb_data);
    
    comp::mesh mesh = comp::load_from_file(asset_path + "models/unit_cube.obj");
    Component::set<comp::mesh>(throw_entity, mesh);
    
    comp::material mat = comp::create_new(asset_path + "/textures/dev_grid_orange_512.png");
    //comp::material_controller::set(player_entity, std::move(ground_mat));
    Component::set(throw_entity, mat);
  }
  
  // Fwd Entity
  {
    math::transform trans = math::transform_init(math::vec3_init(0, 0, 0), math::vec3_init(0.05f, 0.05f, 0.05f), math::quat());
    Component::set(fwd_entity, trans);
    
    comp::mesh mesh = comp::load_from_file(asset_path + "models/unit_cube.obj");
    Component::set<comp::mesh>(fwd_entity, mesh);
    
    comp::material mat = comp::create_new(asset_path + "/textures/dev_grid_blue_512.png");
    //comp::material_controller::set(player_entity, std::move(ground_mat));
    Component::set(fwd_entity, mat);
  }
}


void
init_systems()
{
  // Platform logging.
  util::set_log_types(util::log_msg_types::errors | util::log_msg_types::warnings | util::log_msg_types::info);
  util::set_log_outputs(util::log_out::console | util::log_out::buffer);

  // Reg log callbacks before setup.
  sdl::set_error_callback([](const std::string &str){ util::log_info(str);});
  renderer::set_log_callback([](const uint32_t id, const std::string &str){ util::log_info(std::to_string(id) + " " + str); });

  // Setup
  sys::window::initialize(1280, 600, false, "Wired");
  input.set_mouse_hold(true);
  
  // Init
  renderer::initialize();
  renderer::clear_color(0.2f, 0.3f, 0.3f);
  
  Sys::Debug_line_renderer::initialize();
  Sys::Physics_world::initialize();
  
  assert(sys::script_env::initialize());
  script_bindings_v01::bind_api(sys::script_env::get_as_engine());
  
  
  sys::script_env::test_hook();
}