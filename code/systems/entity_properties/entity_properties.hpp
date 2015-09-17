#ifndef ENTITY_PROPERTIES_INCLUDED_44762D12_12B4_4216_AED0_438DDCDB3C27
#define ENTITY_PROPERTIES_INCLUDED_44762D12_12B4_4216_AED0_438DDCDB3C27


#include <core/entity/entity.hpp>
#include <string>
#include <vector>
#include <map>
#include <stdint.h>


namespace Sys {


class Entity_properties
{
public:

  explicit                  Entity_properties();
                            ~Entity_properties() {}
  
  bool                      add_entity(const Core::Entity e);
  bool                      remove_entity(const Core::Entity e);
  bool                      has_entity(const Core::Entity e);
  
  std::string               get_name(const Core::Entity e) const;
  bool                      set_name(const Core::Entity e, const std::string &name);
  
  std::vector<std::string>  get_tags(const Core::Entity e) const;
  bool                      has_tag(const Core::Entity e, const std::string &tag) const;
  bool                      add_tag(const Core::Entity e, const std::string &tag);
  bool                      remove_tag(const Core::Entity e, const std::string tag);
  bool                      clear_tags(const Core::Entity e);
  
private:

  struct Properties
  {
    std::string               name;
    std::vector<std::string>  tags;
  };

  std::map<const Core::Entity, Properties> m_properties;
  
}; // class


} // ns


#endif // include guard