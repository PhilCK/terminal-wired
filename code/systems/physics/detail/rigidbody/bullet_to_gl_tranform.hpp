#ifndef BULLET_TO_GL_TRANSFORM_INCLUDED_9014E3EA_57EB_4582_824A_4EA911D32B06
#define BULLET_TO_GL_TRANSFORM_INCLUDED_9014E3EA_57EB_4582_824A_4EA911D32B06


#include <math/transform/transform.hpp>
#include <bullet/btBulletDynamicsCommon.h>


namespace Bullet {
namespace Detail {


inline math::transform
bullet_to_gl(const btTransform &transform)
{
  const auto rotation         = transform.getRotation();
  const math::quat rb_quat    = math::quat_init(rotation.x(), rotation.y(), rotation.z(), rotation.w());
  const math::mat3 rot_mat    = math::quat_get_rotation_matrix(rb_quat);
  const math::mat3 rot_mat_tr = math::mat3_get_transpose(rot_mat);
  const math::quat rb_quat2   = math::quat_init_with_mat3(rot_mat_tr);
  
  const auto pos_data         = transform.getOrigin();
  const math::vec3 rb_pos     = math::vec3_init(pos_data.x(), pos_data.y(), pos_data.z());
  
  math::transform adjusted_transform;
  adjusted_transform.rotation = rb_quat2;
  adjusted_transform.position = rb_pos;
  adjusted_transform.scale    = math::vec3_one(); // This might not be correct, Assuming that no scale from bullet.
  
  return adjusted_transform;
}


inline btTransform
gl_to_bullget(const math::transform &transform)
{
  math::quat bt_friendly_rot;
  {
    const math::mat3 rot_mat    = math::quat_get_rotation_matrix(transform.rotation);
    const math::mat3 rot_mat_tr = math::mat3_get_transpose(rot_mat);
    
    bt_friendly_rot = math::quat_init_with_mat3(rot_mat_tr);
  }
  
  btTransform adjusted_transform;
  adjusted_transform.setOrigin(btVector3(math::vec3_get_x(transform.position),
                                         math::vec3_get_y(transform.position),
                                         math::vec3_get_z(transform.position)));

  adjusted_transform.setRotation(btQuaternion(math::quat_get_x(bt_friendly_rot),
                                              math::quat_get_y(bt_friendly_rot),
                                              math::quat_get_z(bt_friendly_rot),
                                              math::quat_get_w(bt_friendly_rot)));

  return adjusted_transform;
}


} // ns
} // ns


#endif // inc guard