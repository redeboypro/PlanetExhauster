#include "Obstacle.h"

Map::Obstacle::Obstacle(Entity* entity, Rigidbody* rigidbody, const glm::ivec2 &size, int maxCount)
        : m_entity(entity), m_rigidbody(rigidbody), m_size(size), m_maxCount(maxCount) {
    m_rigidbody->isKinematic = true;
    m_entity->setActive(false);
}
