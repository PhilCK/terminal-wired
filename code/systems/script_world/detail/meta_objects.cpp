
#include <systems/script_world/detail/meta_objects.hpp>
#include <systems/script_world/script_world_manager.hpp>
#include <components/transform/transform_controller.hpp>
#include <components/rigid_body/rigid_body_controller.hpp>
#include <utils/logging.hpp>
#include <assert.h>


namespace Meta_object {


Physics::Physics(const Generic &owner)
: m_owner(owner)
{
}


void
Physics::set_mass(const float new_mass)
{
  Rigidbody::set_mass(m_owner.get_entity_id(), new_mass);
}


float
Physics::get_mass() const
{
  util::log_error("not yet impl");
  return 1.0f;
}


void
Physics::set_solid(const bool set_solid)
{
  Rigidbody::set_trigger(m_owner.get_entity_id(), !set_solid);
}


bool
Physics::is_solid() const
{
  util::log_error("not yet impl");
  return true;
}


void
Physics::apply_force(const float x, const float y, const float z)
{
  Rigidbody::apply_world_force(m_owner.get_entity_id(), math::vec3_init(x, y, z));
}


void
Physics::set_collision_callback(const std::function<void(const Generic &)> &cb)
{
  if(m_owner.get_script_mgr())
  {
    m_owner.get_script_mgr()->set_collision_callback(m_owner.get_entity_id(), cb);
  }
}


Material::Material()
{
}


void
Material::set_color(const float r, const float g, const float b)
{
  util::log_error("not yet impl");
}


void
Material::set_emissive(const bool em)
{


  util::log_error("not yet impl");
}


bool
Material::is_emissive() const
{
  util::log_error("not yet impl");
  return false;
}


Transform::Transform(Generic &owner)
: m_owner(&owner)
{
}


void
Transform::set_position(const float x, const float y, const float z)
{
  const Core::Entity e = m_owner->get_entity_id();
  math::transform trans;
  
  if(Component::get(e, trans))
  {
    trans.position = math::vec3_init(x, y, z);
    assert(Component::set(e, trans));
  }
  else
  {
    util::log_error("Couldn't find transform.");
  }
}


float
Transform::get_x() const
{
  const Core::Entity e = m_owner->get_entity_id();
  assert(Core::entity_as_uint(e));
  
  math::transform trans;
  
  if(Component::get(e, trans))
  {
    return math::vec3_get_x(trans.position);
  }
  
  util::log_error("Couldn't find transform.");
  return 0.f;
}


float
Transform::get_y() const
{
  const Core::Entity e = m_owner->get_entity_id();
  assert(Core::entity_as_uint(e));
  
  math::transform trans;
  
  if(Component::get(e, trans))
  {
    return math::vec3_get_y(trans.position);
  }
  
  util::log_error("Couldn't find transform.");
  return 0.f;
}


float
Transform::get_z() const
{
  const Core::Entity e = m_owner->get_entity_id();
  assert(Core::entity_as_uint(e));
  
  math::transform trans;
  
  if(Component::get(e, trans))
  {
    return math::vec3_get_z(trans.position);
  }
  
  util::log_error("Couldn't find transform.");
  return 0.f;
}


void
Transform::set_euler(const float x, const float y, const float z)
{
  util::log_error("not yet impl");
}


float
Transform::get_pitch() const
{
  util::log_error("not yet impl");
  return 1.f;
}


float
Transform::get_yaw() const
{
  util::log_error("not yet impl");
  return 1.f;
}


float
Transform::get_roll() const
{
  util::log_error("not yet impl");
  return 1.f;
}


void
Transform::set_scale(const float x, const float y, const float z)
{
  const Core::Entity e = m_owner->get_entity_id();
  math::transform trans;
  Rigidbody::Rigidbody_data rb_data;
  
  if(Component::get(e, trans) /*&& Component::get(e, rb_data)*/)
  {
    trans.scale = math::vec3_init(x, y, z);
    assert(Component::set(e, trans));
    
    // TODO need to set physics stuff as well.
  }
  else
  {
    util::log_error("Couldn't find transform.");
  }
}


float
Transform::get_scale_x() const
{
  const Core::Entity e = m_owner->get_entity_id();
  assert(Core::entity_as_uint(e));
  
  math::transform trans;
  
  if(Component::get(e, trans))
  {
    return math::vec3_get_x(trans.scale);
  }
  
  util::log_error("Couldn't find transform.");
  return 0.f;
}


float
Transform::get_scale_y() const
{
  const Core::Entity e = m_owner->get_entity_id();
  assert(Core::entity_as_uint(e));
  
  math::transform trans;
  
  if(Component::get(e, trans))
  {
    return math::vec3_get_y(trans.scale);
  }
  
  util::log_error("Couldn't find transform.");
  return 0.f;
}


float
Transform::get_scale_z() const
{
  const Core::Entity e = m_owner->get_entity_id();
  assert(Core::entity_as_uint(e));
  
  math::transform trans;
  
  if(Component::get(e, trans))
  {
    return math::vec3_get_z(trans.scale);
  }
  
  util::log_error("Couldn't find transform.");
  return 0.f;
}


Mesh::Mesh()
{
}


Generic::Generic(const uint32_t entity_id, Sys::Script::Script_manager *mgr)
: m_entity(Core::uint_as_entity(entity_id))
, m_script_mgr(mgr)
, m_transform(*this)
, m_physics(*this)
{
}


Generic::~Generic()
{

}


void
Generic::set_update_callback(const Update_callback &cb)
{
  if(m_script_mgr)
  {
    m_script_mgr->set_update_callback(m_entity, cb);
  }
}


void
Generic::set_thrown_callback(const Thrown_callback &cb)
{
  if(m_script_mgr)
  {
    m_script_mgr->set_thrown_callback(m_entity, cb);
  }
}


} // ns