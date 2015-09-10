#ifndef SCRIPT_MANAGER_INCLUDED_76D2AA0E_C60E_4303_B282_7B76EF6B35FE
#define SCRIPT_MANAGER_INCLUDED_76D2AA0E_C60E_4303_B282_7B76EF6B35FE


#include <systems/script/detail/meta_objects.hpp>
#include <core/entity/entity.hpp>
#include <stdint.h>
#include <string>
#include <map>
#include <vector>


namespace Sys {
namespace Script {


class Script_manager
{
  
                  Script_manager(const Script_manager&) = delete;
  Script_manager& operator=(const Script_manager&) = delete;
                  Script_manager(Script_manager&&) = delete;
  Script_manager& operator=(const Script_manager&&) = delete;

public:

  explicit        Script_manager();
                  ~Script_manager();

  bool            add_script(const Core::Entity entity, const std::string &code);
  bool            remove_script(const Core::Entity entity);
  
  void            schedule_collision_callback(const Core::Entity entity);
  void            schedule_message_callback(const Core::Entity entity, const std::string &str);

  void            think();
  
private:

  friend class Meta_object::Generic;
  friend class Meta_object::Physics;
  
  void set_thrown_callback(const Core::Entity e, const Meta_object::Thrown_callback &cb);
  void set_update_callback(const Core::Entity e, const Meta_object::Update_callback &cb);
  void set_message_callback(const Core::Entity e, const Meta_object::Message_callback &cb);
  void set_collision_callback(const Core::Entity e, const Meta_object::Collision_callback &cb);
  
private:

  std::map<Core::Entity, Meta_object::Generic>  m_objects;
  std::map<Core::Entity, Meta_object::Collision_callback>                   m_collision_callbacks;
  std::map<Core::Entity, Meta_object::Update_callback>                   m_update_callbacks;
  std::map<Core::Entity, Meta_object::Thrown_callback>
    m_thrown_callbacks;
  std::map<Core::Entity, Meta_object::Message_callback
  >
    m_message_callbacks;
  
  std::vector<Core::Entity> m_thrown_queue;
  std::vector<Core::Entity> m_collision_queue;
  
}; // class


} // ns
} // ns


#endif // include guard