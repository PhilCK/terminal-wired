/*
  The implimentation details could be abstracted into a class to
  help deal with states or worlds etc.
  
  This will need to be modified to deal with one off life time callbacks
  on_start_on_end.
*/
#include <core/schedular/schedular.hpp>
#include <vector>
#include <queue>
#include <assert.h>


namespace
{
  // TODO: Pull the 'id' out of this, noise in the cache.
  // Although each function call will flush the cache?
  using Callback_data = std::tuple<uint32_t, Core::Schedule_callback, void*>;

  std::queue<Callback_data>  on_starts;
  std::vector<Callback_data> on_early_thinks;
  std::vector<Callback_data> on_thinks;
  std::vector<Callback_data> on_late_thinks;
  std::queue<Callback_data>  on_ends;
  
  uint32_t id = 0;
}


namespace Core {
namespace Schedular {


bool
initialize()
{
  // Some general heuristic for reserving space.
  const uint32_t think_size_hint = 128;
  
  on_early_thinks.reserve(think_size_hint >> 2);
  on_thinks.reserve(think_size_hint);
  on_late_thinks.reserve(think_size_hint >> 1);

  return true;
}


bool
de_initialize()
{
  assert(on_starts.empty());
  assert(on_early_thinks.empty());
  assert(on_thinks.empty());
  assert(on_late_thinks.empty());
  assert(on_ends.empty());
  
  return (on_starts.empty() &&
          on_early_thinks.empty() &&
          on_thinks.empty() &&
          on_late_thinks.empty() &&
          on_ends.empty());
}


void
think()
{
  while(!on_starts.empty())
  {
    auto &callback = on_starts.front();
    std::get<1>(callback)(Schedule_task::on_start, std::get<2>(callback));
    on_starts.pop();
  }

  for(auto &callback : on_early_thinks) {
    std::get<1>(callback)(Schedule_task::on_early_think, std::get<2>(callback));
  }
  
  for(auto callback : on_thinks) {
    std::get<1>(callback)(Schedule_task::on_think, std::get<2>(callback));
  }
  
  for(auto callback : on_late_thinks) {
    std::get<1>(callback)(Schedule_task::on_late_think, std::get<2>(callback));
  }
  
  while(!on_ends.empty())
  {
    auto &callback = on_ends.front();
    std::get<1>(callback)(Schedule_task::on_end, std::get<2>(callback));
    on_ends.pop();
  }
}


void
add(Schedule &schedule_owner,
    const Schedule_task task_type,
    Schedule_callback callback,
    void *user_data)
{
  switch(task_type)
  {
    case(Schedule_task::on_start):
      on_starts.emplace(Callback_data{++id, callback, user_data});
    break;
  
    case(Schedule_task::on_early_think):
      on_early_thinks.emplace_back(Callback_data{++id, callback, user_data});
    break;
    
    case(Schedule_task::on_think):
      on_thinks.emplace_back(Callback_data{++id, callback, user_data});
    break;
    
    case(Schedule_task::on_late_think):
      on_late_thinks.emplace_back(Callback_data{++id, callback, user_data});
    break;
    
    case(Schedule_task::on_end):
      on_ends.emplace(Callback_data{++id, callback, user_data});
    break;
  }
}


void
remove(const uint32_t id)
{
  // Remove id
  
}


} // ns
} // ns