#include <systems/script/script_environment.hpp>
#include <add_ons/scriptstdstring/scriptstdstring.h>
#include <utils/string_helpers.hpp>
#include <utils/logging.hpp>
#include <utils/directory.hpp>
#include <assert.h>


namespace
{
  asIScriptEngine *as_engine = nullptr;
  asIScriptContext *as_context = nullptr;
  asIScriptModule *as_module = nullptr;
  
  void as_message_callback(const asSMessageInfo *msg, void *param)
  {
    const std::string output_msg = "AS: "
                                  + std::string(msg->section) + " "
                                  + std::to_string(msg->row) + ", " + std::to_string(msg->col) + " "
                                  + std::string(msg->message);
    
    switch(msg->type)
    {
      case(asMSGTYPE_ERROR):
        util::log_error(output_msg);
        break;
      
      case(asMSGTYPE_WARNING):
        util::log_error(output_msg);
        break;
      
      case(asMSGTYPE_INFORMATION):
        util::log_error(output_msg);
        break;
    }
  }
} // ns


namespace sys {
namespace script_env {


bool
initialize()
{
  assert(as_engine == nullptr);
  if(as_engine != nullptr)
  {
    util::log_error("Failed to initialize as engine, has it already been initialized?");
    return false;
  }

  // Basic setup of building AS building blocks.
  as_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
  
  assert(as_engine);
  if(!as_engine)
  {
    util::log_error("Failed to create AS Engine.");
    return false;
  }
  
  int set_callback = as_engine->SetMessageCallback(asFUNCTION(as_message_callback), 0, asCALL_CDECL);
  
  assert(set_callback >= 0);
  if(set_callback < 0)
  {
    util::log_warning("Failed to create AS message callback.");
  }
  
  RegisterStdString(as_engine);


  return true;
}


asIScriptEngine*
get_as_engine()
{
  return as_engine;
}



void
test_hook()
{
  // Create module and context, this might move off somewhere else, as it will need rebuilding from time to time.
  as_module = as_engine->GetModule("user-programs", asGM_ALWAYS_CREATE);
  
  /*
    Create base class
  */
  
  const std::string base_class = R"(
    // Base class for callbacks
    namespace APIDev
    {
      class Origin
      {
        void on_thrown()    {}
        void on_contact()   {}
        void on_cycle()     {}
        void on_destroy()   {}
      }
    }
  )";
  
  // Load and add the script sections to the module
  const std::string script = util::get_contents_from_file(util::get_resource_path() + "assets/scripts/test_seed.seed");
  as_module->AddScriptSection("Baseclass", base_class.c_str());
  as_module->AddScriptSection("script.as", script.c_str());
  
  // Build the module
  int r = as_module->Build();
  if( r < 0 )
  {
    util::log_error("Failed to build the module.");
    return;
  }
  
  // Get a script context instance. Usually you'll want to reuse a previously
  // created instance to avoid the overhead of allocating the instance with
  // each call.
  as_context = as_engine->CreateContext();
  
  
  class Script_interaction
  {
  public:
  
    Script_interaction(asIScriptModule *module, const std::string &type)
    {
      assert(module); // Can't be null.
      
      asIScriptEngine *engine = module->GetEngine();

      this->type = engine->GetObjectTypeById(module->GetTypeIdByDecl(type.c_str()));
      
      const std::string factory_decl = type + " @" + type + "()";
      asIScriptFunction *function = this->type->GetFactoryByDecl(factory_decl.c_str());
      
      as_context->Prepare(function);
      as_context->Execute();
      
      this->instance = *(asIScriptObject**)as_context->GetAddressOfReturnValue();
      this->instance->AddRef();
      
      this->thrown  = this->type->GetMethodByDecl("void on_thrown()");
      this->contact = this->type->GetMethodByDecl("void on_contact()");
      this->cycle   = this->type->GetMethodByDecl("void on_cycle()");
      this->destroy = this->type->GetMethodByDecl("void on_destroy()");
    }
  
    ~Script_interaction()
    {
      if(instance)
      {
        instance->Release();
        instance = nullptr;
      }
    }
    
    
    void call_on_start()
    {
      call_method(thrown);
    }
    
    
    void call_on_contact()
    {
      call_method(contact);
    }


    void call_on_cycle()
    {
      call_method(cycle);
    }
    
    void call_on_destroy()
    {
      call_method(destroy);
    }
    
  private:
  
    void call_method(asIScriptFunction *func)
    {
      as_context->Prepare(func);
      as_context->SetObject(this->instance);
      int r = as_context->Execute();
      assert(r >= 0);
    }
    
  private:
  
    asIObjectType     *type     = nullptr;
    asIScriptObject   *instance = nullptr;
    asIScriptFunction *thrown   = nullptr;
    asIScriptFunction *contact  = nullptr;
    asIScriptFunction *cycle    = nullptr;
    asIScriptFunction *destroy  = nullptr;
  }; // class

  Script_interaction script_class(as_module, "Program");

  // Find the type.

  
//  script_class.type = as_engine->GetObjectTypeById(as_module->GetTypeIdByDecl("Program"));
//  
//  // Get the factory function from the object type.
//  asIScriptFunction *function = script_class.type->GetFactoryByDecl("Program @Program()");
//  
//  // Prepare the context to call the factory function.
//  as_context->Prepare(function);
//  as_context->Execute();
//  // create the obj.
//  script_class.instance = *(asIScriptObject**)as_context->GetAddressOfReturnValue();
//  script_class.instance->AddRef();
//
//  script_class.thrown  = script_class.type->GetMethodByDecl("void on_thrown()");
//  script_class.contact = script_class.type->GetMethodByDecl("void on_contact()");
//  script_class.cycle   = script_class.type->GetMethodByDecl("void on_cycle()");
//  script_class.destroy = script_class.type->GetMethodByDecl("void on_destroy()");
  
  // Prepare the context for calling the method
//  as_context->Prepare(script_class.thrown);
//  as_context->SetObject(script_class.instance);
// r = as_context->Execute();
// 
//  as_context->Prepare(script_class.contact);
//  as_context->SetObject(script_class.instance);
//   r = as_context->Execute();
//  
//  as_context->Prepare(script_class.cycle);
//  as_context->SetObject(script_class.instance);
//   r = as_context->Execute();
//  
//  as_context->Prepare(script_class.destroy);
//  as_context->SetObject(script_class.instance);
//  r = as_context->Execute();

  script_class.call_on_start();
  script_class.call_on_contact();
  script_class.call_on_cycle();
  script_class.call_on_destroy();
  
  if( r == asEXECUTION_FINISHED )
  {
    // The return value is only valid if the execution finished successfully
    //asDWORD ret = as_context->GetReturnDWord();
  }
  else
  {
    util::log_error("Error running script.");
  }
  
  // Release the context when you're done with it
  as_context->Release();
  
  
  // Release the object, should kill it.
  //script_class.instance->Release();
}


} // ns
} // ns