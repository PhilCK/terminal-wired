#ifndef CAMERA_INCLUDED_912C1B3C_0FFA_4D33_88F4_2901F23CFC99
#define CAMERA_INCLUDED_912C1B3C_0FFA_4D33_88F4_2901F23CFC99


#include <math/math.hpp>
#include <stdint.h>


namespace comp {

class camera
{
public:

  explicit          camera(const uint32_t width    = 640,
                           const uint32_t height   = 480,
                           const float near_plane  = 0.1f,
                           const float far_plane   = 100.f,
                           const float fov_radians = math::quart_tau());

  math::mat4        get_proj_matrix() const;
  
private:

  uint32_t          m_dimentions    = 0;    // 32   // 128 bytes. too large reduce!
  float             m_near_plane    = 0.f; // 32
  float             m_far_plane     = 0.f; // 32
  float             m_fov_radians   = 0.f; // 32

}; // class

} // namespace


#endif // include guard