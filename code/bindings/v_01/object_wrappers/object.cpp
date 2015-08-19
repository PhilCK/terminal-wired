#include <bindings/v_01/object_wrappers/object.hpp>
#include <utils/logging.hpp>


namespace Obj_wrapper {


void
obj_ctor(void *mem)
{
  new(mem) Object();
}


void
obj_dtor(void *mem)
{
  static_cast<Object*>(mem)->~Object();
}


Object::Object()
{
  util::log_info("obj ctor'd");
}


Object::~Object()
{
  util::log_info("obj '" + m_name + "' dtor'd");
}


}