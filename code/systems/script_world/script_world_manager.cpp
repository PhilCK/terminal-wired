#include <systems/script_world/script_world_manager.hpp>
#include <systems/script_world/detail/meta_objects.hpp>
#include <systems/script_world/detail/chai_binding.hpp>
#include <systems/script_world/detail/chai_instances.hpp>
#include <utils/logging.hpp>
#include <utils/directory.hpp>


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
  
  m_objects.erase(entity);
  m_objects.insert(
    std::pair<Core::Entity, Object>(
      entity,
      Object {
        std::unique_ptr<Meta_object::Generic>(new Meta_object::Generic(Core::entity_as_uint(entity), this)),
        std::unique_ptr<chaiscript::ChaiScript>(new chaiscript::ChaiScript({util::get_resource_path()}))
      })
  );
  
  namespace chai_s = chaiscript;
  auto ch = /*new chaiscript::ChaiScript({util::get_resource_path()});*/ ch_instance.get();
  
  //try
  {
    static Core::Entity e;
    e = entity;
  
    auto get_seed = [this]()
    {
      return m_objects.at(e).meta.get();
    };
  
    // chai.add(fun(&MyClass::method2, &obj, 3), "method2");
  
    Script_detail::Chai_binding::get_binding_module()->add(chai_s::fun(get_seed), "get_seed");
    
    m_objects.at(entity).chai->add(Script_detail::Chai_binding::get_binding_module());
    //ch->add(chai_s::fun(get_seed), "get_seed");
    m_objects.at(entity).chai->add(chai_s::var(m_objects.at(entity).meta.get()), "seed");
    //ch->add_global(chai_s::var(m_objects.at(entity).get()), "seed"); // I think this will barf when ch is resued.
    m_objects.at(entity).chai->eval(code);
  }
  //catch(...)
  {
    //util::log_error("Therewe was an error with chai");
    //assert(false);
    //return false;
  }
  
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
  
  for(const auto collision : m_collision_queue)
  {
    const Core::Entity e = collision.e;
  
    if(m_objects.count(e) && m_collision_callbacks.count(e))
    {
      if(m_objects.count(collision.collided_with))
      {
        auto obj = m_objects.at(collision.collided_with).meta.get();
        m_collision_callbacks[e](*obj);
      }
      else
      {
        auto obj = Meta_object::Generic(Core::entity_as_uint(collision.collided_with), this);
        m_collision_callbacks[e](obj);
      }
    }
  }
  m_collision_queue.clear(); 
  
  for(const auto &cb : m_update_callbacks)
  {
    cb.second();
  }
}


void
Script_manager::schedule_collision_callback(const Core::Entity e, const Core::Entity collided_with)
{
  if(m_objects.count(e))
  {
    m_collision_queue.emplace_back(Collision_data{e, collided_with});
  }
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