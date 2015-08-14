#ifndef TRANSFORM_CONTROLLER_INCLUDED_45F231CE_FAE6_4EF3_9AA6_6D0BDB95EC96
#define TRANSFORM_CONTROLLER_INCLUDED_45F231CE_FAE6_4EF3_9AA6_6D0BDB95EC96


#include <core/entity/entity.hpp>
#include <math/math.hpp>


namespace comp {
namespace transform_controller {


bool              add_transform(const core::entity add_transform);
math::transform   get_transform(const core::entity get_transform);
void              set_transform(const core::entity set_transform, const math::transform &new_transform);


} // namespace
} // namespace


#endif // include guard