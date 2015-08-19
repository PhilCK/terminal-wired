#ifndef OBJECT_WRAPPER_INCLUDED_A1052D29_B345_485E_B186_505B070D041E
#define OBJECT_WRAPPER_INCLUDED_A1052D29_B345_485E_B186_505B070D041E


#include <string>
#include <bindings/v_01/object_wrappers/geometry.hpp>
#include <bindings/v_01/object_wrappers/material.hpp>


namespace Obj_wrapper {


void obj_ctor(void *mem);   //! This is used by Angelscript.
void obj_dtor(void *mem);   //! This is used by Angelscript.


class Object
{
public:

  explicit              Object();
                        ~Object();
  
  inline void           set_name(const std::string &set)  { m_name = set;       }
  inline std::string    get_name() const                  { return m_name;      }
  
  inline void           set_geometry(const Geometry &geo) { m_geometry = geo;   }
  inline Geometry&      get_geometry()                    { return m_geometry;  }
  
  inline void           set_material(const Material &mat) { m_material = mat;   }
  inline Material&      get_material()                    { return m_material;  }
  
private:

  std::string           m_name;
  Geometry              m_geometry;
  Material              m_material;

}; // class


} // ns


#endif // inc guard