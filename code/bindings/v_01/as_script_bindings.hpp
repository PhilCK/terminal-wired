#ifndef AS_SCRIPT_BINDINGS_INCLUDED_EA508600_F9E1_408D_8E51_53E7700576C6
#define AS_SCRIPT_BINDINGS_INCLUDED_EA508600_F9E1_408D_8E51_53E7700576C6


#include <angelscript.h>
#include <utils/directory.hpp>
#include <utils/logging.hpp>


void MessageCallback(const asSMessageInfo *msg, void *param)
{
  const char *type = "ERR ";
  if( msg->type == asMSGTYPE_WARNING ) 
    type = "WARN";
  else if( msg->type == asMSGTYPE_INFORMATION ) 
    type = "INFO";
  printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

// Load the entire script file into a string buffer
void LoadScriptFile(const std::string &filename, std::string &script)
{
  // Open the file in binary mode
  FILE *f = fopen(filename.c_str(), "rb");
  
  // Determine the size of the file
  fseek(f, 0, SEEK_END);
  int len = ftell(f);
  fseek(f, 0, SEEK_SET);
  
  // Load the entire file in one call
  script.resize(len);
  fread(&script[0], len, 1, f);
  
  fclose(f);
}


void test_log()
{
  util::log_info("foo");
}


namespace script_bindings {


void
temp_as_binding_init()
{
  asIScriptEngine *engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
  engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);
  
  engine->RegisterGlobalFunction("void log()", asFUNCTION(test_log), asCALL_CDECL);
  
  // Create a new script module
  asIScriptModule *mod = engine->GetModule("module", asGM_ALWAYS_CREATE);
  // Load and add the script sections to the module
  std::string script;
  LoadScriptFile(util::get_resource_path() + "assets/scripts/test_seed.seed", script);
  mod->AddScriptSection("script.as", script.c_str());
  // Build the module
  int r = mod->Build();
  if( r < 0 )
  {
    // The build failed. The message stream will have received  
    // compiler errors that shows what needs to be fixed
  }
  
  // Get a script context instance. Usually you'll want to reuse a previously
  // created instance to avoid the overhead of allocating the instance with
  // each call.
  asIScriptContext *ctx = engine->CreateContext();
  // Obtain the function from the module. This should preferrably  
  // be cached if the same function is called multiple times.
  asIScriptFunction *func = engine->GetModule("module")->GetFunctionByDecl("void main()");
  // Prepare() must be called to allow the context to prepare the stack
  ctx->Prepare(func);
  // Set the function arguments

  r = ctx->Execute();
  if( r == asEXECUTION_FINISHED )
  {
    // The return value is only valid if the execution finished successfully
    asDWORD ret = ctx->GetReturnDWord();
  }
  // Release the context when you're done with it
  ctx->Release();
}


} // namespace


#endif // include guard