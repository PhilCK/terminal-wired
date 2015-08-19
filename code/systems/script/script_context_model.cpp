#include <systems/script/script_context_model.hpp>
#include <assert.h>


namespace Sys {
namespace Script {


Script_context_model::Script_context_model(const std::string &context_name, asIScriptEngine *engine)
{
  assert(engine);
  
  m_module = engine->GetModule(context_name.c_str(), asGM_ALWAYS_CREATE);
  assert(m_module);
  
  const std::string base_class = R"(
    namespace APIDev
    {
      class Origin
      {
        void on_thrown()    {}
        void on_contact()   {}
        void on_cycle()     {}
        void on_destroy()   {}
        
        void self() {} // Todo return self obj
      }
    }
  )";
  
  int r = m_module->AddScriptSection("Origin", base_class.c_str()); assert(r >= 0);
  
  m_context = engine->CreateContext();
  assert(m_context);
  
  const uint32_t size_hint = 16;
  m_scripts.reserve(size_hint);
}


void
Script_context_model::update()
{
}


uint32_t
Script_context_model::instance_script(const std::string &name, const std::string &script)
{
  m_scripts.emplace_back(Script_data(nullptr, nullptr, ""));
  return 0;
}


bool
Script_context_model::remove_script()
{
  return false;
}


} // ns
} // ns