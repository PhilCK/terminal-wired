#ifndef COLLIDER_INFO_INCLUDED_B3718B86_1AE8_48F6_97C9_32E0550A90CA
#define COLLIDER_INFO_INCLUDED_B3718B86_1AE8_48F6_97C9_32E0550A90CA


namespace Rigidbody {


enum Collision_shape_id
{
  unkown,
  box,
  capsule,
  static_plane,
};


struct Box_collidern
{
  Collision_shape_id id = Collision_shape_id::box;
  float x_extents, y_extents, z_extents;
};


struct Static_plane_collidern
{
  Collision_shape_id id = Collision_shape_id::static_plane;
  float normal_x, normal_y, normal_z, offset;
};


struct Capsule_collidern
{
  Collision_shape_id id = Collision_shape_id::capsule;
  float radius, height;
};


struct Uknown_collider
{
  Collision_shape_id id = Collision_shape_id::unkown;
  float arg_1, arg_2, arg_3, arg_4;
};


} // ns


#endif // include guard