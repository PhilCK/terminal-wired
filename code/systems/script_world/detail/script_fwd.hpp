#ifndef SCRIPT_FWD_INCLUDED_C8F4DAC3_8820_4371_BFD6_50185236DA38
#define SCRIPT_FWD_INCLUDED_C8F4DAC3_8820_4371_BFD6_50185236DA38


#include <functional>


namespace Script_detail {

class Chai_instance;

} // ns


namespace Meta_object {

class Generic;
class Physics;
class Transform;
class Mesh;
class Material;

using Update_callback     = std::function<void()>;
using Thrown_callback     = std::function<void()>;
using Message_callback    = std::function<void(const std::string &)>;
using Collision_callback  = std::function<void(const Generic &)>;

} // ns


namespace Sys {
namespace Script {

class Script_manager;

} // ns
} // ns


#endif // include guard