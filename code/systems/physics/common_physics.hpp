#ifndef COMMON_PHYSICS_INCLUDED_7F0CAE28_E6A7_45CE_BCFA_2F72F96E3847
#define COMMON_PHYSICS_INCLUDED_7F0CAE28_E6A7_45CE_BCFA_2F72F96E3847


#include <systems/physics/collider_info.hpp>


namespace Rigidbody {


namespace Axis
{
  enum ENUM
  {
    x = 1 << 0,
    y = 1 << 1,
    z = 1 << 2,
  };
}


enum class Tranform_type
{
  generic,
  actor,
};


struct Construction_info
{
  Tranform_type transform_hint = Tranform_type::generic;

  float mass = 1;
  
  uint32_t rotation_axis = Axis::x | Axis::y | Axis::z;
  uint32_t movement_axis = Axis::x | Axis::y | Axis::z;
  
  union
  {
    Uknown_collider         unkown_collider = {Collision_shape_id::unkown, 0.5f, 0.5f, 0.5f};
    Box_collider            box_collider;
    Capsule_collider        capsule_collider;
    Static_plane_collider   static_plane_collider;
  };
};


} // ns


#endif // inc guard