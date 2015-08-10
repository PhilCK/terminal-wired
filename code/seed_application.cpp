#include <SDL2/SDL.h>
#include <sdl_wrapper/sdl_lazy_include.hpp>
#include <simple_renderer/lazy_include.hpp>
#include <iostream>
#include <string>


namespace
{
  void debug_log(const std::string &log_msg)
  {
    std::cout << log_msg << std::endl;
  }
}


int
main()
{
  // Reg log callbacks before setup.
  sdl::set_error_callback([](const std::string &str){debug_log(str);});
  renderer::set_log_callback([](const uint32_t id, const std::string &str){ debug_log(std::to_string(id) + " " + str); });

  // Setup
  const sdl::window window(1024, 600, false);
  sdl::ogl_context gl_context(window);
  sdl::input input;
  
  // Init
  renderer::initialize();
  
  while(!window.wants_to_quit())
  {
    sdl::message_pump();
  }

  return 0;
}