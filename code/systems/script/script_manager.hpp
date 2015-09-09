#ifndef SCRIPT_MANAGER_INCLUDED_76D2AA0E_C60E_4303_B282_7B76EF6B35FE
#define SCRIPT_MANAGER_INCLUDED_76D2AA0E_C60E_4303_B282_7B76EF6B35FE


#include <core/entity/entity.hpp>
#include <stdint.h>
#include <string>
#include <vector>


namespace Sys {
namespace Script {


class Script_manager
{

  // No move copy?

public:

  explicit        Script_manager();

  bool            add_script(const Core::Entity entity, const std::string &code);
  bool            remove_script(const Core::Entity entity);
  
  void            schedule_collision_callback(const Core::Entity entity);
  void            schedule_thrown_callback(const Core::Entity entity);
  void            schedule_message_callback(const Core::Entity entity, const std::string &str);

  void            think();
  
private:

  std::vector<int> m_generic_objects;
  std::vector<int> m_collision_callbacks;
  std::vector<int> m_update_callbacks;
  std::vector<int> m_thrown_callbacks;

}; // class


} // ns
} // ns


#endif // include guard