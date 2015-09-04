#include <systems/script/script_engine.hpp>
#include <utils/logging.hpp>
#include <utils/directory.hpp>


namespace
{
  chaiscript::ChaiScript chai({util::get_resource_path()});
}


namespace Sys {
namespace Script_engine {


void
initialize()
{
  chai.add(chaiscript::fun(&util::log_error),   "log_error");
  chai.add(chaiscript::fun(&util::log_warning), "log_warning");
  chai.add(chaiscript::fun(&util::log_info),    "log_info");
}


chaiscript::ChaiScript&
get_chai()
{
  return chai;
}


} // ns
} // ns