#ifndef SCRIPT_CONTROLLER_INCLUDED_3F2B4133_DCB9_4FC2_968D_A6639817FE89
#define SCRIPT_CONTROLLER_INCLUDED_3F2B4133_DCB9_4FC2_968D_A6639817FE89


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include <components/script/script.hpp>
#include <string>


namespace Script_utils {


comp::Script generate_script_data(const std::string &filename);
void update();


} // namespace


namespace Script {


struct Script_data
{
};


void        call_start_hook(const Core::Entity e);
void        call_update_hook(const Core::Entity e);
void        call_contact_hook(const Core::Entity e);


}



namespace Component {


template<>
bool add<Script::Script_data>(const Core::Entity e);


template<>
bool set<Script::Script_data>(const Core::Entity e, const Script::Script_data &component);


template<>
bool get<Script::Script_data>(const Core::Entity e, Script::Script_data &component);


} // namespace


#endif // include guard