#ifndef EVENT_CONTROLLER_INCLUDED_2609CB6D_C9FC_453E_AAB6_3F6A4B45AD3A
#define EVENT_CONTROLLER_INCLUDED_2609CB6D_C9FC_453E_AAB6_3F6A4B45AD3A


#include <core/world/world.hpp>
#include <stdint.h>
#include <cstdlib>


namespace Core {


typedef bool (*Event_callback)(const uint32_t event_id, const void *event_data);


namespace Event {


bool        initialize();
bool        de_initialize();

void        add_callback(const uint32_t event_id, Event_callback callback_func);

void        remove_callback(const uint32_t event_id, Event_callback callback_func);

void*       add_event_to_queue(const uint32_t event_id, const uint32_t size_of_data);
void        deliver_events();


} // namespace
} // namespace


#endif // include guard