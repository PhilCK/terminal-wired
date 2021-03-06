#ifndef WINDOW_INCLUDED_01AE1B71_DF3C_4C50_ADF6_675710FC76D0
#define WINDOW_INCLUDED_01AE1B71_DF3C_4C50_ADF6_675710FC76D0


#include <stdint.h>
#include <string>


namespace sys {
namespace window {


uint32_t          get_width();
uint32_t          get_height();
bool              set_resolution(const uint32_t width, const uint32_t height);

bool              is_fullscreen();
bool              set_fullscreen(const bool set);

std::string       get_title();
bool              set_title(const std::string &str);

bool              is_open();

bool              initialize(const uint32_t width, const uint32_t height, const bool is_fullscreen, const std::string &title);
void              de_initialize();
void              think();


} // namespace
} // namespace


#endif // include guard