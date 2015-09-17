#include <systems/entity_properties/entity_properties.hpp>
#include <utils/logging.hpp>
#include <algorithm>


namespace Sys {


Entity_properties::Entity_properties()
{
}


bool
Entity_properties::add_entity(const Core::Entity e)
{
  if(!m_properties.count(e))
  {
    m_properties.insert(std::pair<const Core::Entity, Properties>(
      e,
      Properties {
        "entity", {}
      }
    ));
    
    return true;
  }
  else
  {
    const std::string ent_id = std::to_string(Core::entity_as_uint(e));
    util::log_error("Entity_properties - already has this entity '" + ent_id + "'");
  }
  
  return false;
}


bool
Entity_properties::remove_entity(const Core::Entity e)
{
  if(m_properties.count(e))
  {
    m_properties.erase(e);
    return true;
  }
  else
  {
    const std::string ent_id = std::to_string(Core::entity_as_uint(e));
    util::log_error("Entity_properties - couldn't find entity '" + ent_id + "'");
  }
  
  return false;
}


bool
Entity_properties::has_entity(const Core::Entity e)
{
  return !!m_properties.count(e);
}


std::string
Entity_properties::get_name(const Core::Entity e) const
{
  if(m_properties.count(e))
  {
    return m_properties.at(e).name;
  }
  else
  {
    const std::string ent_id = std::to_string(Core::entity_as_uint(e));
    util::log_error("Enity_properties - couldn't find entity to retive name '" + ent_id + "'");
  }
  
  return "";
}


bool
Entity_properties::set_name(const Core::Entity e, const std::string &set_name)
{
  if(m_properties.count(e))
  {
    m_properties.at(e).name = set_name;
    return true;
  }
  else
  {
    const std::string ent_id = std::to_string(Core::entity_as_uint(e));
    util::log_error("Enity_properties - couldn't find entity to set name '" + ent_id + "'");
  }
  
  return "";
}


std::vector<std::string>
Entity_properties::get_tags(const Core::Entity e) const
{
  if(m_properties.count(e))
  {
    return m_properties.at(e).tags;
  }
  else
  {
    const std::string ent_id = std::to_string(Core::entity_as_uint(e));
    util::log_error("Enity_properties - couldn't find entity to get tags '" + ent_id + "'");
  }
  
  return {};
}



bool
Entity_properties::has_tag(const Core::Entity e, const std::string &tag) const
{
  if(m_properties.count(e))
  {
    const auto &tags = m_properties.at(e).tags;
    
    const auto it = std::find_if(std::begin(tags), std::end(tags), [tag](const std::string &curr_tag){ return curr_tag == tag; });
    
    return it != std::end(tags);
  }
  else
  {
    const std::string ent_id = std::to_string(Core::entity_as_uint(e));
    util::log_error("Enity_properties - couldn't find entity to search tags '" + ent_id + "'");
  }
  
  return false;
}


bool
Entity_properties::add_tag(const Core::Entity e, const std::string &tag)
{
  if(m_properties.count(e))
  {
    m_properties.at(e).tags.emplace_back(tag);
    return true;
  }
  else
  {
    const std::string ent_id = std::to_string(Core::entity_as_uint(e));
    util::log_error("Enity_properties - couldn't find entity to add tag '" + ent_id + "'");
  }
  
  return false;
}


bool
Entity_properties::remove_tag(const Core::Entity e, const std::string tag)
{
  if(m_properties.count(e))
  {
    auto &tags = m_properties.at(e).tags;
    
    auto it = std::find_if(std::begin(tags), std::end(tags), [tag](const std::string &curr_tag){ return curr_tag == tag; });
    
    if(it != std::end(tags))
    {
      tags.erase(it);
      return true;
    }
    else
    {
      util::log_warning("Entity_properties - tag not found to remove.");
    }
  }
  else
  {
    const std::string ent_id = std::to_string(Core::entity_as_uint(e));
    util::log_error("Enity_properties - couldn't find entity to remove tag '" + ent_id + "'");
  }
  
  return false;
}


bool
Entity_properties::clear_tags(const Core::Entity e)
{
  if(m_properties.count(e))
  {
    m_properties.at(e).tags.clear();
    return true;
  }
  else
  {
    util::log_error("Enity_properties - couldn't find entity to clear tags");
  }
  
  return false;
}


} // ns