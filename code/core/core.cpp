#include <core/core.hpp>
#include <core/time/time.hpp>


namespace Core {


void
initialize()
{
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
}


} // ns