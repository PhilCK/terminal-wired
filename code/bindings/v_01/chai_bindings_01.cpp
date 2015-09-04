#include <bindings/v_01/chai_bindings_01.hpp>
#include <core/entity/entity.hpp>
#include <components/material/material_controller.hpp>
#include <utils/directory.hpp>

namespace
{
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
initialize(chaiscript::ModulePtr module)
{
  module->add(chaiscript::user_type<generic_object>(), "object");
  module->add(chaiscript::constructor<generic_object()>(), "object");
  module->add(chaiscript::fun(&generic_object::set_id), "set_id");
  module->add(chaiscript::fun(&generic_object::get_material), "get_material");
  
  module->add(chaiscript::user_type<material_object>(), "material");
  module->add(chaiscript::constructor<material_object()>(), "material");
  module->add(chaiscript::fun(&material_object::set_color), "set_color");
}


} // ns