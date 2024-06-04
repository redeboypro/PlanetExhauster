//
// Created by probn on 01.06.2024.
//

#include "ObstaclesGrid.h"

Map::ObstaclesGrid::ObstaclesGrid(Entity *entity, Rigidbody *rigidbody, const glm::ivec2 &size, World *world)
        : m_world(world), m_entity(entity), m_rigidbody(rigidbody), m_size(size) {
    m_rigidbody->isKinematic = true;

    m_grid = std::vector<std::vector<bool>>(size.x);

    for (std::vector<bool> &o: m_grid) {
        o = std::vector<bool>(size.y);
    }
}

void Map::ObstaclesGrid::add(const Map::Obstacle &obstacle, int x, int y) {
    for (int i = 0; i < obstacle.getSize().x; i++) {
        for (int j = 0; j < obstacle.getSize().y; j++) {
            m_grid[x + i][y + j] = true;
        }
    }

    Rigidbody* instantiated = m_world->instantiate(World::defaultLayer);
    instantiated->isKinematic = true;
    Entity *obstacleEnt = instantiated->getEntity();

    obstacleEnt->setLocalPosition(obstacle.getEntity()->getLocalPosition());
    obstacleEnt->setMesh(obstacle.getEntity()->getMesh());
    obstacleEnt->setTexture(obstacle.getEntity()->getTexture());

    m_entity->addChild(obstacleEnt);

    glm::vec3 startPos = obstacleEnt->getLocalPosition();

    obstacleEnt->setLocalPosition(-m_entity->worldToLocal(
            glm::vec3(startPos.x + static_cast<float>(x) * OBSTACLE_XZ_OFFSET, OBSTACLE_Y_OFFSET, startPos.z + static_cast<float>(y) * (-OBSTACLE_XZ_OFFSET))));

    obstacleEnt->setLocalScale(glm::vec3(0.1));
}

bool Map::ObstaclesGrid::hasAt(int x, int y) {
    return m_grid[x][y];
}
