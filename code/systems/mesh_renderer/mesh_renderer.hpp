#ifndef MESH_RENDERER_INCLUDED_D1732E86_BC5A_4604_B96A_ACF5FB0C51BB
#define MESH_RENDERER_INCLUDED_D1732E86_BC5A_4604_B96A_ACF5FB0C51BB


#include <core/entity/entity.hpp>
#include <math/mat/mat4.hpp>


namespace Sys {
namespace Mesh_renderer {


void initialize();
void render(const Core::Entity entity, const math::mat4 &view_proj);


} // ns
} // ns


#endif // inc guard