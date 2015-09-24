#include <common/object_factory.hpp>
#include <systems/physics/rigidbody_controller.hpp>
#include <systems/transform/transform_controller.hpp>
#include <systems/script_world/script_world_controller.hpp>
#include <systems/mesh_renderer/mesh_renderer_controller.hpp>
#include <systems/window/window.hpp>
#include <math/transform/transform.hpp>
#include <utils/directory.hpp>
#include <utils/string_helpers.hpp>

// to die
#include <components/camera/camera_controller.hpp>
#include <components/mesh/mesh_controller.hpp>
#include <components/mesh_renderer/mesh_renderer_controller.hpp>
#include <components/material/material_controller.hpp>


namespace
{
  const std::string asset_path = util::get_resource_path() + "assets/";
}


namespace Object_factory {


Core::Entity
create_local_input_actor(const Core::World w)
{
  const Core::Entity player_entity = Core::generate_entity(2);
  
    // Renderer
  {
    Mesh_renderer::add(w, player_entity);
  }
  
    math::transform player_transform = math::transform_init(math::vec3_init(0, 3, 0), math::vec3_one(), math::quat());
    Transform::add(w, player_entity, player_transform);
    
    // Rigidbody
    {
      Rigidbody::Capsule_collidern coll;
      coll.radius = 0.5f;
      coll.height = 1.f;
      
      Rigidbody::Construction_info rb_info;
      rb_info.mass = 0.1f;
      rb_info.rotation_axis = Rigidbody::Axis::y;
      rb_info.capsule_collider = coll;
      
      Rigidbody::add(w, player_entity, rb_info);
    }
    
    comp::mesh player_mesh = comp::load_from_file(asset_path + "models/unit_cube.obj");
    Component::set<comp::mesh>(player_entity, player_mesh);
    
    comp::material ground_mat = comp::create_new(asset_path + "/textures/dev_grid_red_512.png");
    //comp::material_controller::set(player_entity, std::move(ground_mat));
    Component::set(player_entity, ground_mat);
  
  return player_entity;
}


Core::Entity
create_program_block(const Core::World w)
{
  const Core::Entity throw_entity = Core::generate_entity(4);
 
  // Renderer
  {
    Mesh_renderer::add(w, throw_entity);
  }
  
    math::transform trans = math::transform_init(math::vec3_init(2, 1, 0), math::vec3_one(), math::quat());
    Transform::add(w, throw_entity, trans);

    const std::string code = util::get_contents_from_file(util::get_resource_path() + "assets/scripts/test_seed.seed");
    Script::add(w, throw_entity, code);
    
    // Rigidbody
    {
      Rigidbody::Box_collidern coll;
      coll.x_extents = 0.5f;
      coll.y_extents = 0.5f;
      coll.z_extents = 0.5f;
      
      Rigidbody::Construction_info rb_info;
      rb_info.mass = 3.f;
      rb_info.box_collider = coll;
      
      rb_info.collision_event = true;
      
      Rigidbody::add(w, throw_entity, rb_info);
    }
    
    comp::mesh mesh = comp::load_from_file(asset_path + "models/unit_cube.obj");
    Component::set<comp::mesh>(throw_entity, mesh);
    
    comp::material mat = comp::create_new(asset_path + "/textures/dev_grid_orange_512.png");
    //comp::material_controller::set(player_entity, std::move(ground_mat));
    Component::set(throw_entity, mat);
  
  return throw_entity;
}


Core::Entity
create_camera(const Core::World w)
{
  const Core::Entity camera_entity = Core::generate_entity(3);
  
    math::transform cam_transform = math::transform_init(math::vec3_init(0, 4, 7), math::vec3_one(), math::quat());
  Transform::add(w, camera_entity, cam_transform);
  
  comp::camera set_camera(sys::window::get_width(), sys::window::get_height(), 0.1f, 1000.f, math::quart_tau() / 2);
  Component::set(camera_entity, set_camera);
  
  return camera_entity;
}


Core::Entity
create_non_physics_block(const Core::World w)
{
  const Core::Entity fwd_entity = Core::generate_entity(5);

  // Renderer
  {
    Mesh_renderer::add(w, fwd_entity);
  }

  math::transform trans = math::transform_init(math::vec3_init(0, 0, 0), math::vec3_init(0.05f, 0.05f, 0.05f), math::quat());
  Transform::add(w, fwd_entity, trans);
  
  comp::mesh mesh = comp::load_from_file(asset_path + "models/unit_cube.obj");
  Component::set<comp::mesh>(fwd_entity, mesh);
  
  comp::material mat = comp::create_new(asset_path + "/textures/dev_grid_blue_512.png");
  //comp::material_controller::set(player_entity, std::move(ground_mat));
  Component::set(fwd_entity, mat);
  
  return fwd_entity;
}


Core::Entity
create_static_ground(const Core::World w)
{
  const Core::Entity ground_entity = Core::generate_entity(1);

  math::transform ground_transform = math::transform_init(math::vec3_zero(), math::vec3_init(100, 1, 100), math::quat());
  Transform::add(w, ground_entity, ground_transform);
  
  // Rigidbody
  {
    Rigidbody::Static_plane_collidern coll;
    coll.normal_x = 0;
    coll.normal_y = 1;
    coll.normal_z = 0;
    coll.offset = 0;
    
    Rigidbody::Construction_info rb_info;
    rb_info.mass = 0.f;
    rb_info.movement_axis = 0;
    rb_info.rotation_axis = 0;
    rb_info.static_plane_collider = coll;
    
    Rigidbody::add(w, ground_entity, rb_info);
  }
  
  comp::mesh ground_mesh = comp::load_from_file(asset_path + "models/unit_plane.obj");
  Component::set<comp::mesh>(ground_entity, ground_mesh);
  
  comp::material ground_mat = comp::create_new(asset_path + "/textures/dev_grid_green_512.png");
  Component::set(ground_entity, ground_mat);
  
  return ground_entity;
}


} // ns
