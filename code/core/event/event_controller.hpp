#ifndef EVENT_CONTROLLER_INCLUDED_2609CB6D_C9FC_453E_AAB6_3F6A4B45AD3A
#define EVENT_CONTROLLER_INCLUDED_2609CB6D_C9FC_453E_AAB6_3F6A4B45AD3A


#include <stdint.h>
#include <cstdlib>


namespace Core {
namespace Event {


typedef bool (*event_receiver_func_ptr)(const uint32_t event_id, const uint32_t type_id, const void *data, const std::size_t size_of_data);

void      listen_for_event(const uint32_t event_id, const uint32_t type_id, event_receiver_func_ptr func_ptr);
bool      reserve_event_data(const std::size_t size_of_data, void* start_ptr);
void      deliver_queued_events();
void      deliver_instant_event(const uint32_t event_id, const uint32_t type_id, void* data, const std::size_t size_of_data);


} // namespace
} // namespace


#endif // include guard