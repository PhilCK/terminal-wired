#ifndef COLLIDER_INFO_INCLUDED_B3718B86_1AE8_48F6_97C9_32E0550A90CA
#define COLLIDER_INFO_INCLUDED_B3718B86_1AE8_48F6_97C9_32E0550A90CA


#include <systems/physics/common_physics.hpp>


namespace Rigidbody {


enum Collision_shape_id
{
  unkown,
  box,
  static_plane,
};


struct Box_collider
{
  const Collision_shape_id id = Collision_shape_id::box;
  float x_extents, y_extents, z_extents;
};


struct Static_plane_collider
{
  const Collision_shape_id id = Collision_shape_id::static_plane;
  float normal_x, normal_y, normal_z, offset;
};


struct Uknown_collider
{
  const Collision_shape_id id = Collision_shape_id::unkown;
  float arg_1, arg_2, arg_3, arg_4;
};


struct Construction_info
{
  float mass = 1;
  
  uint32_t rotation_axis = Axis::x | Axis::y | Axis::z;
  uint32_t movement_axis = Axis::x | Axis::y | Axis::z;
  
  union
  {
    Uknown_collider         unkown_collider = {Collision_shape_id::unkown, 0.5f, 0.5f, 0.5f};
    Box_collider            box_collider;
    Static_plane_collider   static_plane_collider;
  };
};



} // ns


#endif // include guard