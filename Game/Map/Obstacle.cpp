#include "Obstacle.h"

Map::Obstacle::Obstacle(const glm::ivec2 &size, int maxCount, Mesh *mesh, World *world)
        : m_size(size), m_maxCount(maxCount) {
    m_rigidbody = world->instantiate(World::defaultLayer);
    m_collider = new Collider(mesh);
    m_rigidbody->setCollisionShapes({m_collider});
    m_rigidbody->isKinematic = true;
    m_entity = m_rigidbody->getEntity();
}

Map::Obstacle::~Obstacle() {
    delete m_collider;
}
