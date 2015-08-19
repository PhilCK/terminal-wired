#ifndef MATERIAL_INCLUDED_E9842FB3_FE07_4571_8E71_9E0DC77254E1
#define MATERIAL_INCLUDED_E9842FB3_FE07_4571_8E71_9E0DC77254E1


namespace Obj_wrapper {


enum class Color
{
  RED,
  GREEN,
  BLUE,
}; // enum


class Material
{
public:

  explicit            Material();
                      ~Material();

  inline void         set_color(const Color set)  { m_color = set;  }
  inline Color        get_color() const           { return m_color; }

private:

  Color               m_color;

}; // class


void mat_ctor(void *mem); //! Used by Angelscript.
void mat_dtor(void *mem); //! Used by Angelscript.
void mat_cctor(void *mem, const Material &other);; //! Used by Angelscript.


} // ns


#endif // inc guard