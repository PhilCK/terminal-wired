#ifndef AS_SCRIPT_BINDINGS_INCLUDED_EA508600_F9E1_408D_8E51_53E7700576C6
#define AS_SCRIPT_BINDINGS_INCLUDED_EA508600_F9E1_408D_8E51_53E7700576C6


#include <angelscript.h>
#include <utils/directory.hpp>
#include <utils/logging.hpp>
//#include <utils/string_helpers.hpp>
#include <add_ons/scriptstdstring/scriptstdstring.h>


namespace script_bindings_v01 {


void
bind_api(asIScriptEngine *e)
{
  assert(e);

  int r = 0;

  // Dev functions
  // TODO Move these too script-env
  r = e->SetDefaultNamespace("dev");
  r = e->SetDefaultNamespace("dev::log");
  r = e->RegisterGlobalFunction("void info(const ::string &in)",    asFUNCTION(util::log_info),    asCALL_CDECL); assert(r >= 0);
  r = e->RegisterGlobalFunction("void warning(const ::string &in)", asFUNCTION(util::log_warning), asCALL_CDECL); assert(r >= 0);
  r = e->RegisterGlobalFunction("void error(const ::string &in)",   asFUNCTION(util::log_error),   asCALL_CDECL); assert(r >= 0);
  
  
}


} // namespace


#endif // include guard