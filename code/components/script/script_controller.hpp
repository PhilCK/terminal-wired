#ifndef SCRIPT_CONTROLLER_INCLUDED_3F2B4133_DCB9_4FC2_968D_A6639817FE89
#define SCRIPT_CONTROLLER_INCLUDED_3F2B4133_DCB9_4FC2_968D_A6639817FE89


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include <components/script/script.hpp>
#include <systems/script/script_engine.hpp>
#include <string>
#include <functional>


namespace Script_utils {


//comp::Script generate_script_data(const std::string &filename);
//void update();


} // namespace


namespace Script {


  struct Script_data
  {
    Script_data()
    {
      chaiscript::ChaiScript &ch = Sys::Script_engine::get_chai();
      ch.eval(code);
      
      const std::string instance = std::string("auto ") + "moop" + " = Test_program();";
      ch.eval(instance);
      
      m_on_start  = ch.eval<std::function<void()> >(std::string("fun() {") + "moop" + ".on_start(); }");
      m_on_update = ch.eval<std::function<void()> >(std::string("fun() {") + "moop" + ".on_update(); }");
    }
  
    void call_start_hook(const Core::Entity e) { m_on_start(); }
    void call_update_hook(const Core::Entity e) { m_on_update(); }
    void call_contact_hook(const Core::Entity e);
    
    std::function<void()> m_on_start;
    std::function<void()> m_on_update;
    
    std::string code =
    R"(
      class Test_program
      {
        def Test_program()
        {
          log_info("test ctor");
        }
        
        def on_start()
        {
          log_info("on start");
        }
        
        def on_update()
        {
          log_info("on info");
        }
      }
    )";
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