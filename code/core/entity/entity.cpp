#include <core/entity/entity.hpp>
#include <core/event/event.hpp>
#include <core/core_event_ids.hpp>
#include <new>
#include <assert.h>
#include <set>


namespace
{
  uint32_t instance_id = 0;
  std::set<Core::Entity> entities;
}


namespace Core {


Entity
generate_entity(const uint8_t type)
{
  const Entity new_ent{type, ++instance_id};
  
  entities.insert(new_ent);
  
//  void *evt_address = Event::add_event_to_queue(Event_id::entity_new, sizeof(New_entity_event));
//  assert(evt_address);
//  
//  New_entity_event *evt_data = new(evt_address) New_entity_event();
//  assert(evt_data);
//  evt_data->e = new_ent;
//  
  return new_ent;
}


void
destroy_entity(const Entity e)
{
  entities.erase(e);
  
  void *evt_address = Event::add_event_to_queue(Event_id::entity_destroy, sizeof(Destroy_entity_event));
  assert(evt_address);
  
  Destroy_entity_event *evt_data = new(evt_address) Destroy_entity_event();
  assert(evt_data);
  evt_data->e = e;
}


} // ns