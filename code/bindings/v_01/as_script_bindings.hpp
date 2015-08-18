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
  
  // API
  
//  
//  // Create a new script module
//  asIScriptModule *mod = e->GetModule("user-program", asGM_ALWAYS_CREATE);
//  // Load and add the script sections to the module
//  const std::string script = util::get_contents_from_file(util::get_resource_path() + "assets/scripts/test_seed.seed");
//  mod->AddScriptSection("script.as", script.c_str());
//  // Build the module
//  r = mod->Build();
//  if( r < 0 )
//  {
//    // The build failed. The message stream will have received  
//    // compiler errors that shows what needs to be fixed
//  }
//  
//  // Get a script context instance. Usually you'll want to reuse a previously
//  // created instance to avoid the overhead of allocating the instance with
//  // each call.
//  asIScriptContext *ctx = e->CreateContext();
//  // Obtain the function from the module. This should preferrably  
//  // be cached if the same function is called multiple times.
//  asIScriptFunction *func = e->GetModule("user-program")->GetFunctionByDecl("void main()");
//  // Prepare() must be called to allow the context to prepare the stack
//  ctx->Prepare(func);
//  // Set the function arguments
//  r = ctx->Execute();
//  
//  //asIScriptModule *module = engine->GetModule("MyModule");
//  asIObjectType *type = e->GetObjectTypeById(mod->GetTypeIdByDecl("Test"));
//  // Get the factory function from the object type
//  asIScriptFunction *factory = type->GetFactoryByDecl("Test @Test()");
//  // Prepare the context to call the factory function
//  ctx->Prepare(factory);
//  // Execute the call
//  ctx->Execute();
//  asIScriptObject *obj = *(asIScriptObject**)ctx->GetAddressOfReturnValue();
//  obj->AddRef();
//
//  asIScriptFunction *func2 = type->GetMethodByDecl("void huh()");
//  // Prepare the context for calling the method
//  ctx->Prepare(func2);
//  // Set the object pointer
//  ctx->SetObject(obj);
//  // Execute the call
//  //ctx->Execute();
//
//  r = ctx->Execute();
//  if( r == asEXECUTION_FINISHED )
//  {
//    // The return value is only valid if the execution finished successfully
//    asDWORD ret = ctx->GetReturnDWord();
//  }
//  // Release the context when you're done with it
//  ctx->Release();
}


} // namespace


#endif // include guard