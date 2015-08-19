#ifndef SCRIPT_CONTEXT_MODEL_INCLUDED_9C26EE72_9D2A_459F_8F61_4496A9EC000B
#define SCRIPT_CONTEXT_MODEL_INCLUDED_9C26EE72_9D2A_459F_8F61_4496A9EC000B


#include <systems/script/script_data.hpp>
#include <angelscript.h>
#include <stdint.h>
#include <string>
#include <vector>


namespace Sys {
namespace Script {


class Script_context_model
{
public:

  explicit        Script_context_model(const std::string &context_name, asIScriptEngine *engine);
                  ~Script_context_model();
  
  void            update();
  
  uint32_t        add_script(const std::string &name, const std::string &script);
  bool            remove_script();
  
private:

  asIScriptModule           *m_module  = nullptr;
  asIScriptContext          *m_context = nullptr;
  std::vector<Script_data>  m_scripts;

}; // namespace


} // ns
} // ns


#endif // inc guard