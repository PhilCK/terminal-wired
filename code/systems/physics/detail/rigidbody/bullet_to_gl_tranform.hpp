#ifndef BULLET_TO_GL_TRANSFORM_INCLUDED_9014E3EA_57EB_4582_824A_4EA911D32B06
#define BULLET_TO_GL_TRANSFORM_INCLUDED_9014E3EA_57EB_4582_824A_4EA911D32B06


#include <math/transform/transform.hpp>
#include <bullet/btBulletDynamicsCommon.h>


namespace Bullet {
namespace Detail {


inline math::transform
bullet_to_gl(const btTransform &transform)
{
  return math::transform();
}


inline btTransform
gl_to_bullget(const math::transform &transform)
{
  return btTransform();
}


} // ns
} // ns


#endif // inc guard