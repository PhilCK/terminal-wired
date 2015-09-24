#include <core/core.hpp>
#include <core/event/event.hpp>
#include <core/schedular/schedular.hpp>
#include <core/time/time.hpp>


namespace Core {


void
initialize()
{
  Schedular::initialize();
  Event::initialize();
  Time::Detail::initialize();
}


void
think()
{
  Time::Detail::think();
}


void
de_initialize()
{
  Time::Detail::de_initialize();
  Event::de_initialize();
  Schedular::de_initialize();
}


} // ns