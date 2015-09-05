#include <bindings/v_01/chai_bindings_01.hpp>
#include <bindings/v_01/meta_objects.hpp>
#include <core/entity/entity.hpp>
#include <components/material/material_controller.hpp>
#include <utils/directory.hpp>


namespace
{
  class physics_object
  {
    explicit
    physics_object()
    {
    }
    
    
    void
    set_size()
    {
    }
    
    void
    set_mass()
    {
    }
    
    Core::Entity entity;
  };

  class material_object
  {
  public:
  
    explicit
    material_object()
    {
    }
    
    void
    set_color()
    {
      comp::material mat = comp::create_new(util::get_resource_path() + "assets/textures/dev_grid_green_512.png");
      Component::set(entity, mat);
    }
  
    Core::Entity entity;
  
  }; // class

  class generic_object
  {
  public:
  
    explicit
    generic_object()
    : material()
    {
    }
    
    void set_id(const uint32_t id)
    {
      entity = Core::uint_as_entity(id);
      material.entity = entity;
    }
    
    material_object
    get_material() { return material; }
    
    
  private:
  
    Core::Entity entity;
    material_object material;
  
  }; //class
}


namespace Chai_bindings {


void
initialize(chaiscript::ModulePtr mod)
{
  namespace chai_s = ::chaiscript;
  namespace Meta = ::Meta_object;

  mod->add(chai_s::user_type<generic_object>(), "object");
  mod->add(chai_s::constructor<generic_object()>(), "object");
  mod->add(chai_s::fun(&generic_object::set_id), "set_id");
  mod->add(chai_s::fun(&generic_object::get_material), "get_material");
  
  mod->add(chai_s::user_type<material_object>(), "material");
  mod->add(chai_s::constructor<material_object()>(), "material");
  mod->add(chai_s::fun(&material_object::set_color), "set_color");
  
  // Meta object hooks
  mod->add(chai_s::user_type<Meta::Generic>(),              "Seed_object");
  mod->add(chai_s::constructor<Meta::Generic()>(),          "Seed_object");
  mod->add(chai_s::constructor<Meta::Generic(uint32_t)>(),  "Seed_object");
  mod->add(chai_s::fun(&Meta::Generic::get_name),           "get_name");
  mod->add(chai_s::fun(&Meta::Generic::set_name),           "set_name");
  mod->add(chai_s::fun(&Meta::Generic::get_physics),        "get_physics_api");
  mod->add(chai_s::fun(&Meta::Generic::get_material),       "get_material_api");
  mod->add(chai_s::fun(&Meta::Generic::get_transform),      "get_transform_api");
  
  
  mod->add(chai_s::user_type<Meta_object::Physics>(), "Physics_api"); // todo do we need this?
  mod->add(chai_s::constructor<Meta::Physics()>(),    "Physics_api"); // todo do we need this?
  mod->add(chai_s::fun(&Meta::Physics::get_mass),     "get_mass");
  mod->add(chai_s::fun(&Meta::Physics::set_mass),     "set_mass");
  mod->add(chai_s::fun(&Meta::Physics::is_solid),     "is_solid");
  mod->add(chai_s::fun(&Meta::Physics::set_solid),    "set_solid");
  
  mod->add(chai_s::user_type<Meta::Material>(),        "Material_api"); // todo do we need this?
  mod->add(chai_s::constructor<Meta::Material()>(),    "Material_api"); // todo do we need this?
  mod->add(chai_s::fun(&Meta::Material::is_emissive),  "is_emissive");
  mod->add(chai_s::fun(&Meta::Material::set_emissive), "set_emissive");
  mod->add(chai_s::fun(&Meta::Material::set_color),    "set_color");
  
  //mod->add(chai_s::user_type<Meta::Transform>(),        "Transform_api"); // todo do we need this?
  //mod->add(chai_s::constructor<Meta::Transform()>(),    "Transform_api"); // todo do we need this?
  mod->add(chai_s::fun(&Meta::Transform::get_scale_x),  "get_scale_x");
  mod->add(chai_s::fun(&Meta::Transform::get_scale_y),  "get_scale_y");
  mod->add(chai_s::fun(&Meta::Transform::get_scale_z),  "get_scale_z");
  mod->add(chai_s::fun(&Meta::Transform::set_scale),    "set_scale");
  mod->add(chai_s::fun(&Meta::Transform::get_pitch),    "get_pitch");
  mod->add(chai_s::fun(&Meta::Transform::get_yaw),      "get_yaw");
  mod->add(chai_s::fun(&Meta::Transform::get_roll),     "get_roll");
  mod->add(chai_s::fun(&Meta::Transform::set_euler),    "set_angles");
  mod->add(chai_s::fun(&Meta::Transform::get_x),        "get_position_x");
  mod->add(chai_s::fun(&Meta::Transform::get_y),        "get_position_y");
  mod->add(chai_s::fun(&Meta::Transform::get_z),        "get_position_z");
  mod->add(chai_s::fun(&Meta::Transform::set_position), "set_position");
}


} // ns