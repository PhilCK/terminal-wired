#include <bindings/v_01/object_wrappers/material.hpp>
#include <new>


namespace Obj_wrapper {


void
mat_ctor(void *mem)
{
  new(mem) Material();
}


void
mat_dtor(void *mem)
{
  static_cast<Material*>(mem)->~Material();
}


void
mat_cctor(void *mem, const Material &other)
{
  new(mem) Material(other);
}


Material::Material()
{
}


Material::~Material()
{
}


} // ns