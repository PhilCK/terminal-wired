#include <systems/window/window.hpp>
#include <sdl_wrapper/window.hpp>
#include <sdl_wrapper/ogl_context.hpp>
#include <sdl_wrapper/message_pump.hpp>


namespace
{
  sdl::window sdl_window(1024, 600, false, "do while");
  const sdl::ogl_context gl_context(sdl_window);
}



namespace sys {
namespace window {


uint32_t
get_width()
{
  return sdl_window.get_width();
}


uint32_t
get_height()
{
  return sdl_window.get_height();
}


bool
set_resolution(const uint32_t width, const uint32_t height)
{
  return sdl_window.set_resolution(width, height);
}


bool
is_fullscreen()
{
  return sdl_window.is_fullscreen();
}


bool
set_fullscreen(const bool set)
{
  return sdl_window.set_fullscreen(set);
}


std::string
get_title()
{
  return sdl_window.get_title();
}


bool
set_title(const std::string &title)
{
  return sdl_window.set_title(title);
}


bool
is_open()
{
  return !sdl_window.wants_to_quit();
}


bool
initialize(const uint32_t width, const uint32_t height, const bool is_fullscreen, const std::string &title)
{
  //const bool success_res   = set_resolution(width, height);
  //const bool success_full  = set_fullscreen(is_fullscreen);
  //const bool success_title = set_title(title);
  
  return true; //success_res & success_full & success_title;
}


void
de_initialize()
{
}


void
think()
{
  sdl_window.think();
  sdl_window.flip_buffer();
  sdl::message_pump();
}


} // namespace
} // namespace