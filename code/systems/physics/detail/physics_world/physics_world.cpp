#include <systems/physics/detail/physics_world/physics_world.hpp>
#include <assert.h>


namespace Bullet {


World::World()
: m_broadphase()
, m_collisionConfiguration()
, m_dispatcher(&m_collisionConfiguration)
, m_solver()
, m_dynamicsWorld(&m_dispatcher, &m_broadphase, &m_solver, &m_collisionConfiguration)
{
  m_dynamicsWorld.setGravity(btVector3(0, -10, 0));
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
  m_dynamicsWorld.stepSimulation(dt, 10);
  
  // Check collisions
}


} // ns