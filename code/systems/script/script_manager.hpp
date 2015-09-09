#ifndef SCRIPT_MANAGER_INCLUDED_76D2AA0E_C60E_4303_B282_7B76EF6B35FE
#define SCRIPT_MANAGER_INCLUDED_76D2AA0E_C60E_4303_B282_7B76EF6B35FE


#include <stdint.h>
#include <string>
#include <vector>


namespace Sys {


class Script_manager
{
public:

  explicit        Script_manager();

  uint32_t        add_script(const std::string &code);
  void            schedule_collision_callback(const uint32_t id);
  void            schedule_thrown_callback(const uint32_t id);
  void            schedule_message_callback(const std::string &str);

  void            think();
  
private:

  std::vector<int> m_generic_objects;
  std::vector<int> m_collision_callbacks;
  std::vector<int> m_update_callbacks;
  std::vector<int> m_thrown_callbacks;

}; // class


} // ns


#endif // include guard