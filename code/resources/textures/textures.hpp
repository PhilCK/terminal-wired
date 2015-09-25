#ifndef TEXTURES_INCLUDED_E0265454_BEC9_4AFE_8E00_28763777D615
#define TEXTURES_INCLUDED_E0265454_BEC9_4AFE_8E00_28763777D615


#include <resources/textures/texture_resource.hpp>
#include <string>
#include <stdint.h>
#include <memory>


namespace Resource {
namespace Texture_controller {


void                initialize();
void                de_initialize();

Texture_asset       add_texture(const std::string &file);
void                remove_texture(const uint32_t id);


} // ns
} // ns


#endif // incldue guard