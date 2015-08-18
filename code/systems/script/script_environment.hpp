#ifndef SCRIPT_ENV_INCLUDED_37A01FE9_43A5_440F_8E0D_E80BC3B86B58
#define SCRIPT_ENV_INCLUDED_37A01FE9_43A5_440F_8E0D_E80BC3B86B58


#include <angelscript.h>


namespace sys {
namespace script_env {


bool                initialize();
void                de_initialize();

asIScriptEngine*    get_as_engine();

void                test_hook();

} // ns
} // ns


#endif // include guard