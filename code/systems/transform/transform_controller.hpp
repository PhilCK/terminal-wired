#ifndef TRANSFORM_CONTROLLER_INCLUDED_2DCF5319_C078_41E6_A088_23A9E0E4FCAE
#define TRANSFORM_CONTROLLER_INCLUDED_2DCF5319_C078_41E6_A088_23A9E0E4FCAE


#include <core/entity/entity.hpp>
#include <core/world/world.hpp>
#include <math/transform/transform.hpp>
#include <math/vec/vec3.hpp>


namespace Transform {

bool      initialize();
bool      de_initialize();

bool      add(const Core::World w,
              const Core::Entity e,
              const math::transform &t = math::transform_init(math::vec3_zero(), math::vec3_one(), math::quat_init()));
bool      remove(const Core::World w, const Core::Entity e);
bool      get(const Core::World w, const Core::Entity e, math::transform &t);
bool      set(const Core::World w, const Core::Entity e, const math::transform &t);


} // ns


#endif // inc guard