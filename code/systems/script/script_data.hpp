#ifndef SCRIPT_DATA_INCLUDED_A41FDC83_E56A_4706_920A_14706A50DD77
#define SCRIPT_DATA_INCLUDED_A41FDC83_E56A_4706_920A_14706A50DD77


#include <angelscript.h>
#include <string>


namespace Sys {
namespace Script {


class Script_data
{
public:

  explicit                  Script_data(asIScriptContext *context,
                                        asIScriptModule *module,
                                        const std::string &type);
                            ~Script_data();
  
  void                      call_on_start(asIScriptContext *context);
  void                      call_on_contact(asIScriptContext *context);
  void                      call_on_cycle(asIScriptContext *context);
  void                      call_on_destroy(asIScriptContext *context);

private:

  asIObjectType             *m_type     = nullptr;
  asIScriptObject           *m_instance = nullptr;
  asIScriptFunction         *m_thrown   = nullptr;
  asIScriptFunction         *m_contact  = nullptr;
  asIScriptFunction         *m_cycle    = nullptr;
  asIScriptFunction         *m_destroy  = nullptr;
  
}; // class


} // ns
} // ns


#endif // inc guard