//
// Created by probn on 02.06.2024.
//

#include "ObstaclesGenerator.h"

Map::ObstaclesGenerator::ObstaclesGenerator(Map::ObstaclesGrid *grid, std::vector<Map::Obstacle> prefabs, World *world)
        : m_world(world), m_grid(grid), m_prefabs(std::move(prefabs)) {}

bool Map::ObstaclesGenerator::canPlaceAt(int placeX, int placeY, glm::ivec2 size) {
    for (int i = -1; i < size.x + 1; i++) {
        for (int j = -1; j < size.y + 1; j++) {
            if (i < 0 && placeX == 0 || j < 0 && placeY == 0
                || i + placeX > m_grid->getSize().x - 1 || j + placeY > m_grid->getSize().y - 1) {
                continue;
            }

            if (m_grid->hasAt(i + placeX, j + placeY)) {
                return false;
            }
        }
    }

    return true;
}

void Map::ObstaclesGenerator::generate() {
    int obstaclesCount = std::uniform_int_distribution<>
            (0, m_grid->getSize().x * m_grid->getSize().y)(m_generator);

    for (int i = 0; i < obstaclesCount; i++) {
        Obstacle obstacle = m_prefabs[std::uniform_int_distribution<>
                (0, static_cast<int>(m_prefabs.size()))(m_generator)];

        int count = 0;

        for (Obstacle o: m_randomObstacles) {
            if (o.getMaxCount() == obstacle.getMaxCount()) {
                count++;
            }
        }

        if (count >= obstacle.getMaxCount()) {
            continue;
        }

        m_randomObstacles.push_back(obstacle);

        int randomX = std::uniform_int_distribution<>(0, m_grid->getSize().x - 1)(m_generator);
        int randomY = std::uniform_int_distribution<>(0, m_grid->getSize().y - 1)(m_generator);

        if (canPlaceAt(randomX, randomY, obstacle.getSize())) {
            m_grid->add(obstacle, randomX, randomY, m_world);
        }
    }
}
