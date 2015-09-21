#ifndef RIGID_BODY_CONTROLLER_INCLUDED_863E3FCC_12C0_4F20_B5E9_93824F72622B
#define RIGID_BODY_CONTROLLER_INCLUDED_863E3FCC_12C0_4F20_B5E9_93824F72622B


#include <core/entity/entity.hpp>
#include <core/world/world.hpp>
#include <math/vec/vec3.hpp>
#include <math/transform/transform.hpp>


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


struct Construction_info
{
  float mass = 1;
  uint32_t rotation_axis;
  uint32_t movement_axis;
};


bool            add(const Core::World w, const Core::Entity e, const Construction_info &info);
bool            remove(const Core::World w, const Core::Entity e);

void            apply_world_force(const Core::World w, const Core::Entity e, const math::vec3 force);
void            apply_local_force(const Core::World w, const Core::Entity e, const math::vec3 force);

void            set_mass(const Core::World w, const Core::Entity e, const float set_mass);
float           get_mass(const Core::World w, const Core::Entity e);

void            set_move_axis(const Core::World w, const Core::Entity e, const uint32_t axis);
uint32_t        get_move_axis(const Core::World w, const Core::Entity e);
bool            can_move_on_x(const Core::World w, const Core::Entity e);
bool            can_move_on_y(const Core::World w, const Core::Entity e);
bool            can_move_on_z(const Core::World w, const Core::Entity e);

void            set_rotation_axis(const Core::World w, const Core::Entity e, const uint32_t axis);
uint32_t        get_rotation_axis(const Core::World w, const Core::Entity e);
bool            can_rotate_on_x(const Core::World w, const Core::Entity e);
bool            can_rotate_on_y(const Core::World w, const Core::Entity e);
bool            can_rotate_on_z(const Core::World w, const Core::Entity e);

void            set_trigger(const Core::World w, const Core::Entity e, const bool set_trigger);
bool            is_trigger(const Core::World w, const Core::Entity e);

void            set_gravity(const Core::World w, const Core::Entity e, const math::vec3 force);
math::vec3      get_gravity(const Core::World w, const Core::Entity e);

void            set_transform(const Core::World w, const Core::Entity e, const math::transform &transform);
// Get transform through transform component.



} // ns


#endif // inc guard