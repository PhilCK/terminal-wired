#ifndef META_OBJECTS_INCLUDED_3CBFB61C_E1FD_4D84_ABBE_B73023FC4154
#define META_OBJECTS_INCLUDED_3CBFB61C_E1FD_4D84_ABBE_B73023FC4154


#include <core/entity/entity.hpp>
#include <core/world/world.hpp>
#include <systems/script_world/detail/script_fwd.hpp>
#include <string>


namespace Meta_object {


enum class Direction : uint16_t
{
  up,
  down,
  forward,
  backwards,
  left,
  right,
};


class Physics
{
public:

  explicit        Physics(const Generic &owner);
  
  void            apply_force3f(const float x, const float y, const float z);
  void            apply_force(const Direction dir);
  
  void            set_gravity3f(const float x, const float y, const float z);
  void            set_gravity(const Direction dir);
  
  void            set_mass(const float new_mass);
  float           get_mass() const;
  
  void            set_solid(const bool solid);
  bool            is_solid() const;
  
  void            set_collision_callback(const Collision_callback &cb);
  
private:

  const Generic   &m_owner;
  std::function<void(const Generic &)> m_collision_callback;

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

  explicit        Transform(Generic &owner);

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

  Generic *m_owner = nullptr;

}; // class


class Mesh
{
public:

  explicit        Mesh();
  
private:

};


class Generic
{
public:

  explicit            Generic(const uint32_t id = 0, Sys::Script::Script_manager *mgr = nullptr);
                      ~Generic();
  
  void                set_update_callback(const Update_callback &cb);
  void                set_thrown_callback(const Thrown_callback &cb);
  
  inline void         set_name(const std::string &str)   { m_name = str;  }
  inline std::string  get_name() const                   { return m_name; }
  inline std::string  get_id() const                     { return std::to_string(Core::entity_as_uint(m_entity)); }
  
  inline Transform*   get_transform()   { return &m_transform; }
  inline Physics&     get_physics()     { return m_physics;    }
  inline Material&    get_material()    { return m_mat;        }
  inline Mesh&        get_mesh()        { return m_mesh;       }
  
  // Internal API do not expose.
  
  inline Core::Entity get_entity_id() const { return m_entity; }
  inline Core::World  get_world_id() const  { return m_world;  }
  
  inline Sys::Script::Script_manager* get_script_mgr() const { return m_script_mgr; }
  
private:

  std::string                  m_name        = "Seed";
  Core::Entity                 m_entity      = Core::invalid_entity();
  Core::World                  m_world       = Core::World{1}; // temp
  Sys::Script::Script_manager *m_script_mgr  = nullptr;
  Transform                    m_transform;
  Physics                      m_physics;
  Material                     m_mat;
  Mesh                         m_mesh;
  
  std::function<void()> m_update_callback;
  std::function<void()> m_thrown_callback;

}; // class


} // ns


#endif // inc guard