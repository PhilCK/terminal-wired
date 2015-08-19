#include <bindings/v_01/object_wrappers/geometry.hpp>
#include <new>


namespace Obj_wrapper {


void
geo_ctor(void *mem)
{
  new(mem) Geometry();
}


void
geo_dtor(void *mem)
{
  static_cast<Geometry*>(mem)->~Geometry();
}


Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}


} // ns