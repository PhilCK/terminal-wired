#include <core/lazy_include.hpp>
#include <common/world_axis.hpp>
#include <components/script/script_controller.hpp>
#include <components/camera/camera_controller.hpp>
//#include <components/transform/transform_controller.hpp>
#include <components/mesh/mesh_controller.hpp>
#include <components/mesh_renderer/mesh_renderer_controller.hpp>
#include <components/material/material_controller.hpp>
#include <components/rigid_body/rigid_body_controller.hpp>
#include <systems/window/window.hpp>
#include <systems/debug_line_renderer/debug_line_renderer.hpp>
#include <systems/mesh_renderer/mesh_renderer.hpp>
#include <systems/physics_world/physics_world_controller.hpp>
#include <systems/dot_renderer/dot_renderer.hpp>
#include <systems/script_world/script_world_controller.hpp>
#include <utils/directory.hpp>
#include <utils/timer.hpp>
#include <utils/logging.hpp>
#include <utils/string_helpers.hpp>
#include <math/math.hpp>
#include <simple_renderer/lazy_include.hpp>
#include <bullet_wrapper/world.hpp>
#include <bullet_wrapper/rigidbody.hpp>
#include <bullet_wrapper/collider.hpp>
#include <sdl_wrapper/sdl_lazy_include.hpp>
#include <assert.h>
#include <string>
#include <systems/script_world/script_world_manager.hpp>
#include <systems/actor/actor.hpp>
#include <systems/entity_properties/entity_properties.hpp>
#include <systems/transform/transform_controller.hpp>


namespace
{
  const Core::World test_world {1};

  const Core::Entity ground_entity {1,1};
  const Core::Entity player_entity {2,2};
  const Core::Entity camera_entity {3,3};
  const Core::Entity throw_entity  {4,4};
  const Core::Entity fwd_entity    {5,5};
  
  const math::vec3 world_up    = math::vec3_init_with_array(common::world_axis::up);
  const math::vec3 world_fwd   = math::vec3_init_with_array(common::world_axis::fwd);
  const math::vec3 world_left  = math::vec3_init_with_array(common::world_axis::left);
  
  sdl::input input;
  
  bool evt_test(const uint32_t id, const void* data)
  {
    const auto collision_data = static_cast<const Sys::Physics_world::Collision_event*>(data);
    
    if(collision_data->entity_a == throw_entity)
    {
      
    }
  
    return true;
  }
}


void init_systems();
void de_init_systems();
void init_entities();
void update_frame(const float dt);
void render_frame();



namespace test
{

} // class


int
main()
{
  Core::initialize();
  init_systems();
  init_entities();
  
  Sys::Entity_properties sys_entity_properties;
  
  // Core
  
  util::timer dt_timer;
  dt_timer.start();
  
  while(sys::window::is_open())
  {
    Core::think();
    
    update_frame(Core::Time::get_delta_time());
    render_frame();
    // Render
  }
  
  Core::de_initialize();

  return 0;
}


void
update_frame(const float dt)
{
  Core::Event::deliver_events();
  Core::Schedular::think();
  
  Sys::Script::get_current_script_mgr().think();

  if(input.is_key_down(SDLK_w))
  {
    Actor::move_forward(player_entity, -100 * dt);
    //Rigidbody::apply_local_force(player_entity, math::vec3_init(0, 0, -1));
  }
  if(input.is_key_down(SDLK_s))
  {
    Actor::move_forward(player_entity, +100 * dt);
    //Rigidbody::apply_local_force(player_entity, math::vec3_init(0, 0, 1));
  }
  if(input.is_key_down(SDLK_a))
  {
    Rigidbody::apply_local_force(player_entity, math::vec3_init(-100 * dt, 0, 0));
  }
  if(input.is_key_down(SDLK_d))
  {
    Rigidbody::apply_local_force(player_entity, math::vec3_init(+100  * dt, 0, 0));
  }
  if(input.get_mouse_delta_x() != 0)
  {
    //Rigidbody::apply_local_torque(player_entity, math::vec3_init(0, input.get_mouse_delta_x() * 0.1f, 0));
    Actor::turn_right(player_entity, input.get_mouse_delta_x() * dt);
  }
  if(input.is_key_down(SDLK_SPACE))
  {
    // Get player entity fwd vec.
    math::transform player_transform;
    //assert(Component::get(player_entity, player_transform));
    Transform::get(test_world, player_entity, player_transform);
    
    const auto player_fwd  = math::quat_rotate_point(player_transform.rotation, world_fwd);
    const auto throw_dir   = math::vec3_add(player_fwd, math::vec3_init(0, 0.7, 0));
    const auto throw_scale = math::vec3_scale(throw_dir, 30000.f * dt);
    
    math::transform throw_transform;
    throw_transform.rotation = player_transform.rotation;
    throw_transform.position = math::vec3_add(player_transform.position, player_fwd);
    
    const std::string code = util::get_contents_from_file(util::get_resource_path() + "assets/scripts/test_seed.seed");
    Component::Script_component throw_program(code);
    Component::set(throw_entity, throw_program);    
    
    Rigidbody::set_transform(throw_entity, throw_transform);
    Rigidbody::apply_world_force(throw_entity, throw_scale);
  }
  
  // Move fwd entity
  {
    math::transform player_transform;
    //assert(Component::get(player_entity, player_transform));
    assert(Transform::get(test_world, player_entity, player_transform));

    const auto player_fwd = math::quat_rotate_point(player_transform.rotation, world_fwd);

    math::transform trans;
    //assert(Component::get(fwd_entity, trans));
    Transform::get(test_world, fwd_entity, trans);

    trans.position = math::vec3_add(player_transform.position, player_fwd);
    Transform::set(test_world, fwd_entity, trans);
  }

  Sys::Physics_world::update_world(dt);
  comp::rigid_body_controller::update_world(dt);
  //Actor::update_transforms(); // Called after physics stuff.
  input.think();
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
  assert(Transform::get(test_world, player_entity, trans));
  
  const math::vec3 fwd = math::quat_rotate_point(trans.rotation, world_fwd);
  
  comp::camera current_camera;
  Component::get(camera_entity, current_camera);
  const auto proj = current_camera.get_proj_matrix();
  
  math::transform cam_transform;
  //Component::get<math::transform>(camera_entity, cam_transform);
  Transform::get(test_world, camera_entity, cam_transform);
  
  //const math::mat4 view = math::mat4_lookat(cam_transform.position, math::vec3_zero(), math::vec3_init(0, 1, 0));
  const math::mat4 view = math::mat4_lookat(trans.position, math::vec3_add(trans.position, fwd), math::quat_rotate_point(trans.rotation, world_up));
  const math::mat4 view_proj = math::mat4_multiply(view, proj);

  // Render Scene
  {
    Sys::Mesh_renderer::render(player_entity, view_proj);
    Sys::Mesh_renderer::render(throw_entity,  view_proj);
    Sys::Mesh_renderer::render(fwd_entity,    view_proj);
    Sys::Dot_renderer::render(ground_entity, view_proj);
  }
  
  // Debug lines
  {
    const math::vec3 fwd = math::quat_rotate_point(trans.rotation, world_fwd);
    const math::vec3 up  = math::quat_rotate_point(trans.rotation, world_up);
  
    comp::camera current_camera;
    Component::get(camera_entity, current_camera);
    const auto proj = current_camera.get_proj_matrix();
    
    math::transform cam_transform;
    //Component::get<math::transform>(camera_entity, cam_transform);
    Transform::get(test_world, camera_entity, cam_transform);
  
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
//  Component::Script_component foo(util::get_resource_path() + "assets/scripts/test_program.seed");

  // Hook up collision event for test.
  //Core::Event::add_callback(123, Script::collision_callback);

  const std::string asset_path = util::get_resource_path() + "assets/";

  // Camera
  {
    math::transform cam_transform = math::transform_init(math::vec3_init(0, 4, 7), math::vec3_one(), math::quat());
    //Component::set(camera_entity, cam_transform);
    Transform::add(test_world, camera_entity, cam_transform);
    
    comp::camera set_camera(sys::window::get_width(), sys::window::get_height(), 0.1f, 1000.f, math::quart_tau() / 2);
    Component::set(camera_entity, set_camera);
  }
  
  // Ground
  {
    math::transform ground_transform = math::transform_init(math::vec3_zero(), math::vec3_init(100, 1, 100), math::quat());
    //Component::set<math::transform>(ground_entity, ground_transform);
    Transform::add(test_world, ground_entity, ground_transform);
    
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
    
    //Component::set(player_entity, player_transform);
    Transform::add(test_world, player_entity, player_transform);
  
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
    //Component::set(throw_entity, trans);
    Transform::add(test_world, throw_entity, trans);

    const std::string code = util::get_contents_from_file(util::get_resource_path() + "assets/scripts/test_seed.seed");
    Component::Script_component throw_program(code);
    Component::set(throw_entity, throw_program);
    
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
    //Component::set(fwd_entity, trans);
    Transform::add(test_world, fwd_entity, trans);
    
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
  Core::Schedular::initialize();
  Core::Event::initialize();
  
  renderer::initialize();
  renderer::clear_color(0.2f, 0.3f, 0.3f);
  
  Sys::Debug_line_renderer::initialize();
  Sys::Physics_world::initialize();
  Sys::Script::initialize();
}


void
de_init_systems()
{
  Core::Schedular::de_initialize();
}