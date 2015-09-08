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


  struct Script_data
  {
    uint32_t ch_id = 0;
    // Make a chaiscript pool so we can pull chaiscript instances out.
    // And replace them.
  
    Script_data()
    {}
  
    Script_data(Core::Entity id)
    {
      ch_id = Sys::Script_engine::add_chai_instance();
      chaiscript::ChaiScript &ch = Sys::Script_engine::get_chai(ch_id);
      
      //ch.eval(code);
      
      // Phil mem leak, decide how this is going to get implimented.
      m_generic.reset(new Meta_object::Generic(Core::entity_as_uint(id)));
      m_generic->set_name("foofy");
      
      ch.add(Sys::Script_engine::get_module());
      chaiscript::ChaiScript::State some_state = ch.get_state();
      
      ch.set_state(some_state);
      
      ch.add_global(chaiscript::var(m_generic), "seed");
      //ch.eval("GLOBAL _self = Seed_object(" + std::to_string(Core::entity_as_uint(id)) + ")");
      ch.eval_file(util::get_resource_path() + "assets/scripts/test_seed.seed");
    }
    
    ~Script_data()
    {

    }
  
    void call_thrown_hook()
    {
      chaiscript::ChaiScript &ch = Sys::Script_engine::get_chai(ch_id);
      ch.eval("seed.on_thrown();");
    }
    
    void call_update_hook()
    {
      chaiscript::ChaiScript &ch = Sys::Script_engine::get_chai(ch_id);
      ch.eval("seed.on_update();");
    }
    
    void call_contact_hook(const Core::Entity e);
    
    std::shared_ptr<Meta_object::Generic> m_generic;
  };


} // ns



namespace Component {


template<>
bool add<Script::Script_data>(const Core::Entity e);


template<>
bool set<Script::Script_data>(const Core::Entity e, const Script::Script_data &component);


template<>
bool get<Script::Script_data>(const Core::Entity e, Script::Script_data &component);


} // namespace


#endif // include guard