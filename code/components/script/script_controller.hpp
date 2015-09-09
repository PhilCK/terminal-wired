#ifndef SCRIPT_CONTROLLER_INCLUDED_3F2B4133_DCB9_4FC2_968D_A6639817FE89
#define SCRIPT_CONTROLLER_INCLUDED_3F2B4133_DCB9_4FC2_968D_A6639817FE89


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include <components/script/script.hpp>
#include <systems/script/script_engine.hpp>
#include <bindings/v_01/meta_objects.hpp>
#include <utils/directory.hpp>
#include <string>
#include <functional>
#include <stdint.h>



namespace Script_utils {


//comp::Script generate_script_data(const std::string &filename);
//void update();


} // namespace


namespace Script {


  void call_update_hook();
  
  void call_thrown_hook();
  void call_collision_hook();


  bool collision_callback(const uint32_t id, const void* data);


  struct Script_data
  {
    uint32_t ch_id = 0;
    
    Script_data()
    {}
    
    Script_data(Core::Entity id)
    {
      ch_id = Sys::Script_engine::add_chai_instance();
      chaiscript::ChaiScript &ch = Sys::Script_engine::get_chai(ch_id);
      
      m_generic.reset(new Meta_object::Generic(Core::entity_as_uint(id)));
      
      ch.add(Sys::Script_engine::get_module());
      chaiscript::ChaiScript::State some_state = ch.get_state();
      
      ch.set_state(some_state);
      
      ch.add_global(chaiscript::var(m_generic), "seed");
      ch.eval_file(util::get_resource_path() + "assets/scripts/test_seed.seed");
    }
    
    ~Script_data()
    {

    }
  
    void call_thrown_hook()
    {
      if(m_generic)
      {
        m_generic->on_thrown();
      }
    }
    
    void call_update_hook()
    {
      
    }
    
    void call_contact_hook(const Core::Entity e)
    {
      if(m_generic)
      {
        // Need to build an entity.
        Meta_object::Generic foo(0);
        foo.set_name("unkown object");
        m_generic->get_physics().on_collision(foo);
      }
    }
    
    std::shared_ptr<Meta_object::Generic> m_generic;
  };


} // ns



namespace Component {


class Script_component
{
public:

  void          schedule_update_hook();
  void          schedule_thrown_hook();
  void          schedule_collision_hook();
  
  inline bool   is_valid() const { return m_program_id > 0; }
  
private:

  uint32_t m_program_id = 0;

}; // class



template<>
bool add<Script::Script_data>(const Core::Entity e);


template<>
bool set<Script::Script_data>(const Core::Entity e, const Script::Script_data &component);


template<>
bool get<Script::Script_data>(const Core::Entity e, Script::Script_data &component);


} // namespace


#endif // include guard