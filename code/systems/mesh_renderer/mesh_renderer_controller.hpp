#ifndef MESH_RENDERER_CONTROLLER_INCLUDED_DD274B4D_E177_4958_B7AD_FCF0A70E94D3
#define MESH_RENDERER_CONTROLLER_INCLUDED_DD274B4D_E177_4958_B7AD_FCF0A70E94D3


#include <core/entity/entity.hpp>
#include <core/world/world.hpp>
#include <math/mat/mat4.hpp>


namespace Mesh_renderer {


void        create_world(const Core::World w);
void        destroy_world(const Core::World w);

void        add(const Core::World w, const Core::Entity e);
void        remove(const Core::World w, const Core::Entity e);

void        think(const Core::World w, const math::mat4 &view_proj); // Move mat out.


} // ns


#endif // inc guard