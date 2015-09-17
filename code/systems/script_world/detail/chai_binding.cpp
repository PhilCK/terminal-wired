#include <systems/script_world/detail/chai_binding.hpp>
#include <systems/script_world/detail/meta_objects.hpp>
#include <utils/logging.hpp>


namespace
{
  chaiscript::ModulePtr chai_binding_module(new chaiscript::Module());
}


namespace Script_detail {
namespace Chai_binding {


void
initialize()
{
  // Short hand to keep it neat.
  namespace chai_s  = ::chaiscript;
  namespace Meta    = ::Meta_object;
  auto mod          = chai_binding_module;
  
  // Utils
  mod->add(chaiscript::fun(&util::log_error),   "log_error");
  mod->add(chaiscript::fun(&util::log_warning), "log_warning");
  mod->add(chaiscript::fun(&util::log_info),    "log_info");
  
  // Meta object hooks
  mod->add(chai_s::user_type<Meta::Generic>(),                    "Seed_object");
  mod->add(chai_s::constructor<Meta::Generic()>(),                "Seed_object");
  mod->add(chai_s::constructor<Meta::Generic(uint32_t)>(),        "Seed_object");
  mod->add(chai_s::fun(&Meta::Generic::get_name),                 "get_name");
  mod->add(chai_s::fun(&Meta::Generic::set_name),                 "set_name");
  mod->add(chai_s::fun(&Meta::Generic::get_id),                   "get_id");
  mod->add(chai_s::fun(&Meta::Generic::get_physics),              "get_physics_api");
  mod->add(chai_s::fun(&Meta::Generic::get_material),             "get_material_api");
  mod->add(chai_s::fun(&Meta::Generic::get_transform),            "get_transform_api");
  mod->add(chai_s::fun(&Meta::Generic::set_update_callback),      "set_update_callback");
  mod->add(chai_s::fun(&Meta::Generic::set_thrown_callback),      "set_thrown_callback");
  
  //void (MyClass::*)()>(&MyClass::overloadedmethod)
  mod->add(chai_s::fun(&Meta::Physics::set_gravity3f),            "set_gravity");
  mod->add(chai_s::fun(&Meta::Physics::apply_force3f),            "apply_force");
  mod->add(chai_s::fun(&Meta::Physics::get_mass),                 "get_mass");
  mod->add(chai_s::fun(&Meta::Physics::set_mass),                 "set_mass");
  mod->add(chai_s::fun(&Meta::Physics::is_solid),                 "is_solid");
  mod->add(chai_s::fun(&Meta::Physics::set_solid),                "set_solid");
  mod->add(chai_s::fun(&Meta::Physics::set_collision_callback),   "set_collision_callback");
  
  mod->add(chai_s::fun(&Meta::Material::is_emissive),             "is_emissive");
  mod->add(chai_s::fun(&Meta::Material::set_emissive),            "set_emissive");
  mod->add(chai_s::fun(&Meta::Material::set_color),               "set_color");
  
  mod->add(chai_s::user_type<Meta::Transform>(),                  "Transform");
  mod->add(chai_s::fun(&Meta::Transform::get_scale_x),            "get_scale_x");
  mod->add(chai_s::fun(&Meta::Transform::get_scale_y),            "get_scale_y");
  mod->add(chai_s::fun(&Meta::Transform::get_scale_z),            "get_scale_z");
  mod->add(chai_s::fun(&Meta::Transform::set_scale),              "set_scale");
  mod->add(chai_s::fun(&Meta::Transform::get_pitch),              "get_pitch");
  mod->add(chai_s::fun(&Meta::Transform::get_yaw),                "get_yaw");
  mod->add(chai_s::fun(&Meta::Transform::get_roll),               "get_roll");
  mod->add(chai_s::fun(&Meta::Transform::set_euler),              "set_angles");
  mod->add(chai_s::fun(&Meta::Transform::get_x),                  "get_position_x");
  mod->add(chai_s::fun(&Meta::Transform::get_y),                  "get_position_y");
  mod->add(chai_s::fun(&Meta::Transform::get_z),                  "get_position_z");
  mod->add(chai_s::fun(&Meta::Transform::set_position),           "set_position");
}



chaiscript::ModulePtr
get_binding_module()
{
  return chai_binding_module;
}


} // ns
} // ns