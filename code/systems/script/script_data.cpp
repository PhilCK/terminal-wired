#include <systems/script/script_data.hpp>
#include <assert.h>


namespace Sys {
namespace Script {


Script_data::Script_data(asIScriptContext *context,
                         asIScriptModule *module,
                         const std::string &type)
{
  assert(module); // Can't be null.
  
  asIScriptEngine *engine = module->GetEngine();

  m_type = engine->GetObjectTypeById(module->GetTypeIdByDecl(type.c_str()));
  assert(m_type);
  
  const std::string factory_decl = type + " @" + type + "()";
  asIScriptFunction *function = m_type->GetFactoryByDecl(factory_decl.c_str());
  assert(function);

  int r = 0;
  r = context->Prepare(function); assert(r >= 0);
  r = context->Execute(); assert(r >= 0);
  
  m_instance = *(asIScriptObject**)context->GetAddressOfReturnValue();
  assert(m_instance);
  
  m_instance->AddRef();
  
  m_thrown  = m_type->GetMethodByDecl("void on_thrown()"); assert(m_thrown);
  m_contact = m_type->GetMethodByDecl("void on_contact()"); assert(m_type);
  m_cycle   = m_type->GetMethodByDecl("void on_cycle()"); assert(m_cycle);
  m_destroy = m_type->GetMethodByDecl("void on_destroy()"); assert(m_destroy);
}


Script_data::~Script_data()
{
  if(m_instance)
  {
    int r = m_instance->Release(); assert(r >= 0);
    m_instance = nullptr;
  }
}


namespace
{
  void
  call_method(asIScriptFunction *func,
              asIScriptContext *context,
              asIScriptObject *instance)
  {
    int r = 0;
    context->Prepare(func);       assert(r >= 0);
    context->SetObject(instance); assert(r >= 0);
    context->Execute();           assert(r >= 0);

  }
}


void
Script_data::call_on_start(asIScriptContext *context)
{
  call_method(m_thrown, context, m_instance);
}


void
Script_data::call_on_contact(asIScriptContext *context)
{
  call_method(m_contact, context, m_instance);
}


void
Script_data::call_on_cycle(asIScriptContext *context)
{
  call_method(m_cycle, context, m_instance);
}


void
Script_data::call_on_destroy(asIScriptContext *context)
{
  call_method(m_destroy, context, m_instance);
}


} // ns
} // ns