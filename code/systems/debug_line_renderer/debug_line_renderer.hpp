#ifndef DEBUG_LINE_RENDERER_INCLUDED_4DF791CD_8020_4C2A_B56C_0694EFEE159F
#define DEBUG_LINE_RENDERER_INCLUDED_4DF791CD_8020_4C2A_B56C_0694EFEE159F


#include <array>


namespace Sys {
namespace Debug_line_renderer {


bool          initialize();
void          add_line(std::array<float, 3> from, std::array<float,3> to, std::array<float,3> color);
void          render(std::array<float, 16> &wvp);


} // ns
} // ns


#endif // include guard