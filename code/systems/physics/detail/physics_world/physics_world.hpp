#ifndef PHYSICS_WORLD_INCLUDED_A7C24224_E00E_46A8_9E76_328A31D2A1E4
#define PHYSICS_WORLD_INCLUDED_A7C24224_E00E_46A8_9E76_328A31D2A1E4


#include <bullet/btBulletCollisionCommon.h>
#include <bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <memory>
#include <vector>


namespace Bullet {


class World
{
public:

  using Collision_pairs = std::vector<std::pair<void*, void*>>;

  explicit          World();
                    ~World();
  
  void              add_rigidbody(btRigidBody *rb);
  void              remove_rigidbody(btRigidBody *rb);
  void              think(const float dt);
  Collision_pairs   get_collisions();

private:

  btDbvtBroadphase                       m_broadphase;
  btDefaultCollisionConfiguration        m_collisionConfiguration;
  btCollisionDispatcher                  m_dispatcher;
  btSequentialImpulseConstraintSolver    m_solver;
  btDiscreteDynamicsWorld                m_dynamicsWorld;

}; // class


} // ns


#endif // inc guard