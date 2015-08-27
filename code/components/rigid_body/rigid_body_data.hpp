#ifndef RIGID_BODY_INCLUDED_CD31B611_C43F_4444_9054_5986266DA5A7
#define RIGID_BODY_INCLUDED_CD31B611_C43F_4444_9054_5986266DA5A7


#include <core/entity/entity.hpp>
#include <bullet_wrapper/rigidbody.hpp>


namespace Rigidbody {


enum class Collider_type : uint8_t
{
  box,
  capsule,
  sphere,
  static_plane,
};

struct Collider_args
{
  float arg_1, arg_2, arg_3, arg_4;
};

struct Box_collider
{
  float half_extent_x, half_extnet_y, half_extent_z;
};

struct Capsule_collider
{
  float radius, height, arg_3_not_used;
};

struct Sphere_collider
{
  float radius, arg2_not_used, arg3_not_used;
};

struct Static_plane_collider
{
  float normal_x, normal_y, normal_z, offset;
};

struct Collider
{
  Collider_type type = Collider_type::box;

  union
  {
    Box_collider              box_collider_args = {0.5f, 0.5f, 0.5f};
    Capsule_collider          capsule_collider_args;
    Sphere_collider           sphere_collider_args;
    Static_plane_collider     static_plane_collider_args;
    Collider_args             args;
  };
};


struct Rigidbody_data
{
  std::array<float, 3>    gravity   = {0.f, 10.f, 0.f};
  float                   mass      = 1.f;
  Collider                collider;
}; // class


} // ns


#endif // include guard