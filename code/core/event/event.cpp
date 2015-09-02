#include <core/event/event.hpp>
#include <vector>
#include <map>


namespace
{
  std::map<uint32_t, std::vector<Core::Event_callback> > event_listeners;
  
  std::vector<std::pair<uint32_t, uint32_t> > queued_events;
  
  std::vector<uint8_t> event_buffer;
  uint32_t buffer_ptr = 0;
}


namespace Core {
namespace Event {


bool
initialize()
{
  event_buffer.resize(256);

  return true;
}


bool
de_initialize()
{
  return true;
}


void
add_callback(const uint32_t event_id, Event_callback callback_func)
{
  event_listeners[event_id].emplace_back(callback_func);
}


void
remove_callback()
{
}


void *
add_event_to_queue(const uint32_t event_id, const uint32_t size_of_data)
{
  queued_events.push_back(std::pair<uint32_t, uint32_t>(event_id, size_of_data));
  
  if(size_of_data)
  {
    const uint32_t old_buffer_ptr = buffer_ptr;
    buffer_ptr += size_of_data;
    
    return &event_buffer[old_buffer_ptr];
  }
  
  return 0;
}


void
deliver_events()
{
  for(const auto &evt : queued_events)
  {
    for(const auto &cb : event_listeners[evt.first])
    {
      cb(evt.first, nullptr);
    }
  }
  
  buffer_ptr = 0; 
}


} // namespace
} // namespace