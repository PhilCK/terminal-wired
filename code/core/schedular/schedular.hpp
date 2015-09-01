/*
  Schedular
  --
  The main purpose of this is to deal with object lifetimes.
  Some overlap with the event system can be seen here.
  However in general if the callback is lifetime based it should
  be here, if the callback is event based it should be in Events.
*/
#ifndef SCHEDULAR_INCLUDED_EBB5C06B_871B_4965_9DC2_A23D6699C80A
#define SCHEDULAR_INCLUDED_EBB5C06B_871B_4965_9DC2_A23D6699C80A


#include <stdint.h>


namespace Core {


enum class Schedule_task : uint8_t
{
  on_start,
  on_early_think,
  on_think,
  on_late_think,
  on_end,
};


typedef void (*Schedule_callback)(const Schedule_task task_id, void *user_data);


class Schedule
{
public:
  // Not yet implimented.
private:
}; // class


namespace Schedular {


bool        initialize();
bool        de_initialize();

void        think();

void        add(Schedule &schedule_owner,
                const Schedule_task task_type,
                Schedule_callback callback,
                void *user_data);

void        remove(const uint32_t id);


} // Schedular ns


} // Core ns


#endif // inc guard