#include "camera.hpp"


namespace comp {


camera::camera(const uint32_t width, const uint32_t height,
               const float near_plane, const float far_plane,
               const float fov_radians)
: m_dimentions(width << 16 | height << 0)
, m_near_plane(near_plane)
, m_far_plane(far_plane)
, m_fov_radians(fov_radians)
{
}


math::mat4
camera::get_proj_matrix()
{
  return math::mat4_projection(static_cast<float>(m_dimentions >> 16),
                               static_cast<float>(m_dimentions & 0xFFFF),
                               m_near_plane,
                               m_far_plane,
                               m_fov_radians);
}


} // namespace