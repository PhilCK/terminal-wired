#ifndef MESH_RENDERER_INCLUDED_EA864345_D413_4495_94AB_BE0C061F6A73
#define MESH_RENDERER_INCLUDED_EA864345_D413_4495_94AB_BE0C061F6A73


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>


struct mesh_renderer {};


namespace Component {


template<>
bool add<mesh_renderer>(const Core::Entity e);


template<>
bool set<mesh_renderer>(const Core::Entity e, const mesh_renderer &component);


template<>
bool get<mesh_renderer>(const Core::Entity e, mesh_renderer &component);



} // ns


#endif // inc guard