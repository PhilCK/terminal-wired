#include <systems/script/script_manager.hpp>
#include <systems/script/detail/meta_objects.hpp>
#include <systems/script/detail/chai_binding.hpp>
#include <systems/script/detail/chai_instances.hpp>
#include <utils/logging.hpp>
#include <chaiscript/ChaiScript.hpp>
#include <systems/script/detail/meta_objects.hpp>


namespace
{
}


namespace Sys {
namespace Script {


Script_manager::Script_manager()
{
}


Script_manager::~Script_manager()
{
}


bool
Script_manager::add_script(const Core::Entity entity, const std::string &code)
{
  static auto ch_instance = Script_detail::Chai_instances::get_instance();
  
  assert(ch_instance.is_valid());
  if(!ch_instance.is_valid())
  {
    util::log_error("Script_manager - Failed to get a chai instance.");
    return false;
  }
  
  //auto obj = Meta_object::Generic(Core::entity_as_uint(entity), this
  //  );
  //obj.set_name("foofy");
  
  m_objects.insert(
    std::pair<Core::Entity, std::unique_ptr<Meta_object::Generic> >(
      entity,
      std::unique_ptr<Meta_object::Generic>(new Meta_object::Generic(Core::entity_as_uint(entity), this))
  ));
  
  namespace chai_s = chaiscript;
  auto ch = ch_instance.get();
  
  ch->add(Script_detail::Chai_binding::get_binding_module());
  ch->add_global(chai_s::var(m_objects.at(entity).get()), "seed"); // I think this will barf when ch is resued.
  //ch->eval("GLOBAL seed = Seed_object(" + std::to_string(Core::entity_as_uint(entity)) + ")");
  ch->eval(code);
  
  return true;
}


bool
Script_manager::remove_script(const Core::Entity entity)
{
  // Remove from all containers.
  return false;
}


void
Script_manager::think()
{
  // TODO: Need to profile this at some point.
  // TODO: This func needs to run on a thread.

  // Process pending queues
  for(const auto e : m_thrown_queue)
  {
    m_thrown_callbacks[e]();
  }
  m_thrown_queue.clear();
  
  for(const auto e : m_collision_queue)
  {
    if(m_objects.count(e) && m_collision_callbacks.count(e))
    {
      const auto obj = Meta_object::Generic(0, nullptr);
      m_collision_callbacks[e](obj);
    }
  }
  m_collision_queue.clear();
  
  for(const auto &cb : m_update_callbacks)
  {
    cb.second();
  }
}


void
Script_manager::schedule_collision_callback(const Core::Entity entity)
{
  m_collision_queue.emplace_back(entity);
}


void
Script_manager::schedule_message_callback(const Core::Entity entity, const std::string &str)
{
}


void
Script_manager::set_thrown_callback(const Core::Entity e, const Meta_object::Thrown_callback &cb)
{
  if(m_objects.count(e))
  {
    m_thrown_callbacks[e] = cb;
    m_thrown_queue.push_back(e);
  }
  else
  {
    util::log_warning("Script_manager - tried to add callback for an entity that doesn't exsit.");
  }
}


void
Script_manager::set_collision_callback(const Core::Entity e, const Meta_object::Collision_callback &cb)
{
  if(m_objects.count(e))
  {
    m_collision_callbacks[e] = cb;
  }
  else
  {
    util::log_warning("Script_manager - tried to add callback for an entity that doesn't exsit.");
  }
}


void
Script_manager::set_update_callback(const Core::Entity e, const Meta_object::Update_callback &cb)
{
  if(m_objects.count(e))
  {
    m_update_callbacks[e] = cb;
  }
  else
  {
    util::log_warning("Script_manager - tried to add callback for an entity that doesn't exsit.");
  }
}


void
Script_manager::set_message_callback(const Core::Entity e, const Meta_object::Message_callback &cb)
{
  if(m_objects.count(e))
  {
    m_message_callbacks[e] = cb;
  }
  else
  {
    util::log_warning("Script_manager - tried to add callback for an entity that doesn't exsit.");
  }
}


} // ns
} // ns