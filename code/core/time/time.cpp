#include <core/time/time.hpp>
#include <utils/timer.hpp>


namespace
{
  util::timer app_timer;
  float delta_time = 0;
}


namespace Core {
namespace Time {


void
initialize()
{
  app_timer.start();
}


void
think()
{
  delta_time = app_timer.split() * 0.001f;
}


float
get_delta_time()
{
  return delta_time;
}



} // ns
} // ns