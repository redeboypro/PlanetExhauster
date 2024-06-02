//
// Created by probn on 01.06.2024.
//

#include "ObstaclesGrid.h"

Map::ObstaclesGrid::ObstaclesGrid(Entity *entity, Rigidbody *rigidbody, Entity *obstaclesParent, const glm::ivec2 &size)
        : m_entity(entity), m_rigidbody(rigidbody), m_obstaclesParent(obstaclesParent), m_size(size) {
    m_grid.reserve(m_size.x);

    for (std::vector<bool> o: m_grid) {
        o.reserve(m_size.y);
    }
}

void Map::ObstaclesGrid::add(const Map::Obstacle &obstacle, int x, int y, World *world) {
    for (int i = 0; i < obstacle.getSize().x; i++) {
        for (int j = 0; j < obstacle.getSize().y; j++) {
            m_grid[x + i][y + j] = true;
        }
    }

    world->instantiate(obstacle.getRigidbody(), World::defaultLayer);

    m_obstaclesParent->addChild(obstacle.getEntity());
    obstacle.getEntity()->setLocalPosition(glm::vec3(x, 0, y));
}

bool Map::ObstaclesGrid::hasAt(int x, int y) {
    return m_grid[x][y];
}
