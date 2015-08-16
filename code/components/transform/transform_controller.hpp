#ifndef TRANSFORM_CONTROLLER_INCLUDED_45F231CE_FAE6_4EF3_9AA6_6D0BDB95EC96
#define TRANSFORM_CONTROLLER_INCLUDED_45F231CE_FAE6_4EF3_9AA6_6D0BDB95EC96


#include <core/entity/entity.hpp>
#include <core/entity/component_interface.hpp>
#include <math/math.hpp>


namespace component {

template<>
bool add<math::transform>(const core::entity e);

template<>
bool get<math::transform>(const core::entity e, math::transform &get_mesh);


template<>
bool set<math::transform>(const core::entity e, const math::transform &set);


} // namespace


#endif // include guard