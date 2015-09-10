#ifndef SCRIPT_CONTROLLER_INCLUDED_3F2B4133_DCB9_4FC2_968D_A6639817FE89
#define SCRIPT_CONTROLLER_INCLUDED_3F2B4133_DCB9_4FC2_968D_A6639817FE89


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include <components/script/script.hpp>
#include <utils/directory.hpp>
#include <string>
#include <functional>
#include <stdint.h>


namespace Component {


class Script_component
{
public:

  Script_component(const std::string &code)
  : m_script_code(code)
  {}
  
  inline std::string get_code() const { return m_script_code; }

private:
  
  std::string m_script_code;
  
}; // class


template<>
bool add<Script_component>(const Core::Entity e);


template<>
bool set<Script_component>(const Core::Entity e, const Script_component &component);


template<>
bool get<Script_component>(const Core::Entity e, Script_component &component);


} // namespace


#endif // include guard