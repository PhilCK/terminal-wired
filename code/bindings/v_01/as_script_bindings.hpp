#ifndef AS_SCRIPT_BINDINGS_INCLUDED_EA508600_F9E1_408D_8E51_53E7700576C6
#define AS_SCRIPT_BINDINGS_INCLUDED_EA508600_F9E1_408D_8E51_53E7700576C6


#include <angelscript.h>
#include <utils/directory.hpp>
#include <utils/logging.hpp>
#include <bindings/v_01/object_wrappers/geometry.hpp>
#include <bindings/v_01/object_wrappers/material.hpp>
#include <bindings/v_01/object_wrappers/object.hpp>
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
  
  r = e->SetDefaultNamespace("APIDev");
  
  r = e->RegisterEnum("Color");
  r = e->RegisterEnumValue("Color", "RED",    static_cast<uint32_t>(Obj_wrapper::Color::RED));
  r = e->RegisterEnumValue("Color", "GREEN",  static_cast<uint32_t>(Obj_wrapper::Color::GREEN));
  r = e->RegisterEnumValue("Color", "BLUE",   static_cast<uint32_t>(Obj_wrapper::Color::BLUE));
  
  r = e->RegisterObjectType("Geometry", sizeof(Obj_wrapper::Geometry), asOBJ_VALUE | asOBJ_POD); assert(r >= 0);
  r = e->RegisterObjectType("Object",   sizeof(Obj_wrapper::Object),   asOBJ_VALUE); assert(r >= 0);
  r = e->RegisterObjectType("Material", sizeof(Obj_wrapper::Material), asOBJ_VALUE | asOBJ_ASHANDLE); assert(r >= 0);
  
  r = e->RegisterObjectBehaviour("Material", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Obj_wrapper::mat_ctor), asCALL_CDECL_OBJLAST); assert(r >= 0);
  r = e->RegisterObjectBehaviour("Material", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(Obj_wrapper::mat_dtor), asCALL_CDECL_OBJLAST); assert(r >= 0);
  r = e->RegisterObjectBehaviour("Material", asBEHAVE_CONSTRUCT, "void f(const Material &in)", asFUNCTION(Obj_wrapper::mat_cctor), asCALL_CDECL_OBJLAST); assert(r >= 0);
  r = e->RegisterObjectMethod("Material", "void set_color(int)", asMETHOD(Obj_wrapper::Material, set_color), asCALL_THISCALL);
  
  r = e->RegisterObjectBehaviour("Object", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Obj_wrapper::obj_ctor), asCALL_CDECL_OBJLAST); assert(r >= 0);
  r = e->RegisterObjectBehaviour("Object", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Obj_wrapper::obj_dtor), asCALL_CDECL_OBJLAST); assert(r >= 0);
  r = e->RegisterObjectMethod("Object", "void set_name(string& in)", asMETHOD(Obj_wrapper::Object, set_name), asCALL_THISCALL); assert(r >= 0);
  r = e->RegisterObjectMethod("Object", "string get_name() const", asMETHOD(Obj_wrapper::Object, get_name), asCALL_THISCALL); assert(r >= 0);
  r = e->RegisterObjectMethod("Object", "Material& get_material()", asMETHOD(Obj_wrapper::Object, get_material), asCALL_THISCALL); assert(r >= 0);
  r = e->RegisterObjectMethod("Object", "void set_material(const Material &in)", asMETHOD(Obj_wrapper::Object, set_material), asCALL_THISCALL); assert(r >= 0);
}


} // namespace


#endif // include guard