#include <core/time/time.hpp>
#include <utils/timer.hpp>


namespace
{
  util::timer app_timer;
  float delta_time = 0;
}


namespace Core {
namespace Time {

namespace Detail {

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


void
de_initialize()
{
  app_timer.stop();
}

} // detail ns


float
get_delta_time()
{
  return delta_time;
}



} // ns
} // ns