#include <systems/physics/detail/physics_world/physics_world.hpp>
#include <assert.h>


namespace Bullet {


World::World()
: m_broadphase()
, m_collisionConfiguration()
, m_dispatcher(&m_collisionConfiguration)
, m_solver()
, m_dynamicsWorld(&m_dispatcher, &m_broadphase, &m_solver, &m_collisionConfiguration)
, m_debug_draw()
{
  m_dynamicsWorld.setGravity(btVector3(0, -10, 0));
  m_dynamicsWorld.setDebugDrawer(&m_debug_draw);
}


World::~World()
{

}


void
World::add_rigidbody(btRigidBody *rb)
{
  assert(rb);
  m_dynamicsWorld.addRigidBody(rb);
}


void
World::remove_rigidbody(btRigidBody *rb)
{
  assert(rb);
  m_dynamicsWorld.removeRigidBody(rb);
}


void
World::think(const float dt)
{
  //for(int i = 0; i < 10; ++i)
  {
    m_dynamicsWorld.stepSimulation(dt, 10);
  }
  m_dynamicsWorld.debugDrawWorld();
  
  // Check collisions
}


World::Collision_pairs
World::get_collisions()
{
  Collision_pairs collisions;
  
  const uint32_t num_manifolds = m_dynamicsWorld.getDispatcher()->getNumManifolds();

  for (uint32_t i = 0; i < num_manifolds; ++i)
  {
    const btPersistentManifold* contact_manifold = m_dynamicsWorld.getDispatcher()->getManifoldByIndexInternal(i);
    assert(contact_manifold);
    
    const btCollisionObject* obj_a = static_cast<const btCollisionObject*>(contact_manifold->getBody0());
    const btCollisionObject* obj_b = static_cast<const btCollisionObject*>(contact_manifold->getBody1());

    for (int j = 0; j < contact_manifold->getNumContacts(); ++j)
    {
      const btManifoldPoint& pt = contact_manifold->getContactPoint(j);
      
      if (pt.getDistance() < 0.f)
      {
        // Get set user pointers
        void* user_ptr_a = obj_a->getUserPointer();
        void* user_ptr_b = obj_b->getUserPointer();
        
        //const btVector3& ptA       = pt.getPositionWorldOnA();
        //const btVector3& ptB       = pt.getPositionWorldOnB();
        //const btVector3& normalOnB = pt.m_normalWorldOnB;
        
        collisions.emplace_back(std::pair<void*, void*>(user_ptr_a, user_ptr_b));
        collisions.emplace_back(std::pair<void*, void*>(user_ptr_b, user_ptr_a));
      }
    }
  }
  
  return collisions;
}


} // ns