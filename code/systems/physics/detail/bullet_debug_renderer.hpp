#ifndef BULLET_DEBUG_RENDERER_INCLUDED_0326739C_3545_4464_89F0_2FADE5BD9087
#define BULLET_DEBUG_RENDERER_INCLUDED_0326739C_3545_4464_89F0_2FADE5BD9087


#include <bullet/btBulletDynamicsCommon.h>
#include <systems/debug_line_renderer/debug_line_renderer.hpp>
#include <utils/logging.hpp>


namespace Bullet {
namespace Detail {


class Debug_draw : public btIDebugDraw
{
public:

  void
  drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) override
  {
    Sys::Debug_line_renderer::add_line({from.x(), from.y(), from.z()}, {to.x(), to.y(), to.z()}, {color.x(), color.y(), color.z()});
  }
  
  void
  drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) override
  {
    
  }

  void
  reportErrorWarning(const char* warning_string) override
  {
    const std::string error_msg = warning_string;
    util::log_error("Bullet: " + error_msg);
  }
  
  void
  draw3dText(const btVector3 &location, const char *textString) override {}
  
  void
  setDebugMode(int debugMode) override
  {
    m_debugMode = debugMode;
  }
  
  int
  getDebugMode() const override
  {
    return m_debugMode;
  }

private:

  int m_debugMode = btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawContactPoints;


}; // class


} // ns
} // ns


#endif