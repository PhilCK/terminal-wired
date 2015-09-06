#ifndef META_OBJECTS_INCLUDED_3CBFB61C_E1FD_4D84_ABBE_B73023FC4154
#define META_OBJECTS_INCLUDED_3CBFB61C_E1FD_4D84_ABBE_B73023FC4154


#include <core/entity/entity.hpp>
#include <string>
#include <functional>


namespace Meta_object {


class Generic;
class Physics;
class Material;
class Mesh;
class Transform;


class Physics
{
public:

  explicit        Physics(const Generic &owner);
  void            set_mass(const float new_mass);
  float           get_mass() const;
  void            set_solid(const bool solid);
  bool            is_solid() const;
  void            apply_force(const float x, const float y, const float z);
  
private:

  const Generic &m_owner;

}; // class


class Material
{
public:

  explicit        Material();
  void            set_color(const float r, const float g, const float b);
  void            set_emissive(const bool em);
  bool            is_emissive() const;

}; // class


class Transform
{
public:

  explicit        Transform(const Generic &owner);

  void            set_position(const float x, const float y, const float z);
  float           get_x() const;
  float           get_y() const;
  float           get_z() const;
  
  void            set_euler(const float x, const float y, const float z);
  float           get_pitch() const;
  float           get_yaw() const;
  float           get_roll() const;
  
  void            set_scale(const float x, const float y, const float z);
  float           get_scale_x() const;
  float           get_scale_y() const;
  float           get_scale_z() const;
  
private:

  const Generic &m_owner;

}; // class


class Mesh
{
public:

  explicit            Mesh();
  
private:

};


class Generic
{
public:

  explicit            Generic(const uint32_t id = 0);
  void                add_child(Generic &generic);
  void                remove_child(Generic &generic);
  
  void test_callback(const std::function<void(Generic &)> &cb)
  {
    m_test_callback = cb;
    m_test_callback(*this);
  }
  
  inline void         set_name(const std::string &str)   { m_name = str;  }
  inline std::string  get_name() const                   { return m_name; }
  
  inline Transform&   get_transform()   { return m_transform;  }
  inline Physics&     get_physics()     { return m_physics;    }
  inline Material&    get_material()    { return m_mat;        }
  inline Mesh&        get_mesh()        { return m_mesh;       }
  
  inline Core::Entity get_entity_id() const { return m_entity; }
  
private:

  std::string         m_name = "";
  Core::Entity        m_entity = Core::invalid_entity();
  Transform           m_transform;
  Physics             m_physics;
  Material            m_mat;
  Mesh                m_mesh;
  
  std::function<void(Generic &)> m_test_callback;

}; // class


} // ns


#endif // inc guard