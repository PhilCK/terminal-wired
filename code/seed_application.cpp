#include <core/lazy_include.hpp>
#include <common/world_axis.hpp>
#include <common/object_factory.hpp>
#include <components/camera/camera_controller.hpp>
#include <components/mesh/mesh_controller.hpp>
#include <components/mesh_renderer/mesh_renderer_controller.hpp>
#include <components/material/material_controller.hpp>
#include <systems/window/window.hpp>
#include <systems/debug_line_renderer/debug_line_renderer.hpp>
#include <systems/mesh_renderer/mesh_renderer_controller.hpp>
#include <systems/dot_renderer/dot_renderer.hpp>
#include <systems/script_world/script_world_controller.hpp>
#include <utils/directory.hpp>
#include <utils/timer.hpp>
#include <utils/logging.hpp>
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
#include <systems/physics/physics_world_controller.hpp>
#include <systems/physics/rigidbody_controller.hpp>
#include <systems/script_world/script_world_controller.hpp>


namespace
{
  const Core::World test_world {1};

  Core::Entity ground_entity = Core::invalid_entity();
  Core::Entity player_entity = Core::invalid_entity();
  Core::Entity camera_entity = Core::invalid_entity();
  Core::Entity throw_entity  = Core::invalid_entity();
  Core::Entity fwd_entity    = Core::invalid_entity();
  
  const math::vec3 world_up    = math::vec3_init_with_array(common::world_axis::up);
  const math::vec3 world_fwd   = math::vec3_init_with_array(common::world_axis::fwd);
  const math::vec3 world_left  = math::vec3_init_with_array(common::world_axis::left);
  
  sdl::input input;
  
  bool evt_test(const uint32_t id, const void* data)
  {
    const auto collision_data = static_cast<const Physics_world::Collision_event_data*>(data);
    
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
void generate_test_level();


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
  
  Script::get_current_script_mgr().think();

  if(input.is_key_down(SDLK_w))
  {
    //Actor::move_forward(player_entity, -100 * dt);
    Rigidbody::apply_local_force(test_world, player_entity, math::vec3_init(0, 0, -1));
  }
  if(input.is_key_down(SDLK_s))
  {
    Rigidbody::apply_local_force(test_world, player_entity, math::vec3_init(0, 0, +1));
  }
  if(input.is_key_down(SDLK_a))
  {
    Rigidbody::apply_local_force(test_world, player_entity, math::vec3_init(-1, 0, 0));;
  }
  if(input.is_key_down(SDLK_d))
  {
    Rigidbody::apply_local_force(test_world, player_entity, math::vec3_init(+1, 0, 0));
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
    Transform::get(test_world, player_entity, player_transform);
    
    const auto player_fwd  = math::quat_rotate_point(player_transform.rotation, world_fwd);
    const auto throw_dir   = math::vec3_add(player_fwd, math::vec3_init(0, 0.7, 0));
    const auto throw_scale = math::vec3_scale(throw_dir, 30000.f * dt);
    
    Core::destroy_entity(throw_entity);
    throw_entity = Object_factory::create_program_block(test_world);
    
    math::transform throw_transform;
    throw_transform.rotation = player_transform.rotation;
    throw_transform.position = math::vec3_add(player_transform.position, player_fwd);
    
    //const std::string code = util::get_contents_from_file(util::get_resource_path() + "assets/scripts/test_seed.seed");
    //Component::Script_component throw_program(code);
    //Component::set(throw_entity, throw_program);
    //Script::add(test_world, throw_entity, code);
    
    Rigidbody::set_transform(test_world, throw_entity, throw_transform);
    Rigidbody::apply_world_force(test_world, throw_entity, throw_scale);
  }
  
  // Move fwd entity
  {
    math::transform player_transform;
    assert(Transform::get(test_world, player_entity, player_transform));
    
    const auto player_fwd = math::quat_rotate_point(player_transform.rotation, world_fwd);
    
    math::transform trans;
    Transform::get(test_world, fwd_entity, trans);

    trans.position = math::vec3_add(player_transform.position, player_fwd);
    Transform::set(test_world, fwd_entity, trans);
  }

  Physics_world::think(test_world);
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
  Transform::get(test_world, camera_entity, cam_transform);
  
  //const math::mat4 view = math::mat4_lookat(cam_transform.position, math::vec3_zero(), math::vec3_init(0, 1, 0));
  const math::mat4 view = math::mat4_lookat(trans.position, math::vec3_add(trans.position, fwd), math::quat_rotate_point(trans.rotation, world_up));
  const math::mat4 view_proj = math::mat4_multiply(view, proj);

  // Render Scene
  {
    Mesh_renderer::think(test_world, view, proj);
    
    Sys::Dot_renderer::render(ground_entity, view_proj); // This needs to be a material or something.
  }
  
  // Debug lines
  {
    const math::vec3 fwd = math::quat_rotate_point(trans.rotation, world_fwd);
    const math::vec3 up  = math::quat_rotate_point(trans.rotation, world_up);
  
    comp::camera current_camera;
    Component::get(camera_entity, current_camera);
    const auto proj = current_camera.get_proj_matrix();
    
    math::transform cam_transform;
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
  camera_entity = Object_factory::create_camera(test_world);
  ground_entity = Object_factory::create_static_ground(test_world);
  player_entity = Object_factory::create_local_input_actor(test_world);
  throw_entity  = Object_factory::create_program_block(test_world);
  fwd_entity    = Object_factory::create_non_physics_block(test_world);
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
  
  Transform::initialize();
  Script::initialize();
  
  Physics_world::create(test_world);
  Mesh_renderer::create_world(test_world);
  
  generate_test_level();
  
  Sys::Debug_line_renderer::initialize();
}



void
generate_test_level()
{
  const std::string asset_path = util::get_resource_path() + "assets/";

  // 10 x 10 x 5 cubes
  for(int32_t x = -3; x < +3; ++x) {
    for(int32_t y = +0; y < +2; ++y) {
      for(int32_t z = -3; z < +3; ++z)
      {
        Core::Entity level_cube = Core::generate_entity(123);
        
          const uint32_t x_size = rand() % 3 + 1;
          const uint32_t y_size = rand() % 3 + 1;
          const uint32_t z_size = rand() % 3 + 1;
        
          math::transform trans = math::transform_init(math::vec3_init(x * 2, y * 2, z * 2), math::vec3_init(x_size, y_size, z_size), math::quat());
          Transform::add(test_world, level_cube, trans);
        
        // Rb
        {
          Rigidbody::Box_collidern box;
          box.x_extents = static_cast<float>(x_size) * 0.5f;
          box.y_extents = static_cast<float>(y_size) * 0.5f;
          box.z_extents = static_cast<float>(z_size) * 0.5f;
          
          Rigidbody::Construction_info info;
          info.mass = 0;
          info.box_collider = box;
          info.collision_event = false;
          
          Rigidbody::add(test_world, level_cube, info);
        }
        
        // Mesh + mat
        {
          Mesh_renderer::add(test_world, level_cube);
        
          comp::mesh mesh = comp::load_from_file(asset_path + "models/unit_cube.obj");
          Component::set<comp::mesh>(level_cube, mesh);
          
          comp::material mat = comp::create_new(asset_path + "textures/dev_grid_orange_512.png");
          //comp::material_controller::set(player_entity, std::move(ground_mat));
          Component::set(level_cube, mat);
        }
      }
    }
  }
}


void
de_init_systems()
{
  Core::Schedular::de_initialize();
}