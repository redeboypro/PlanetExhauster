//
// Created by probn on 02.06.2024.
//

#ifndef PLANETEXHAUSTER_OBSTACLESGENERATOR_H
#define PLANETEXHAUSTER_OBSTACLESGENERATOR_H

#include "ObstaclesGrid.h"
#include "Obstacle.h"
#include <random>

namespace Map{
    class ObstaclesGenerator
    {
        World* m_world;
        Map::ObstaclesGrid* m_grid;
        std::vector<Map::Obstacle> m_prefabs;

        std::vector<Map::Obstacle> m_randomObstacles;
        std::mt19937 m_generator {std::random_device{}()};

        bool canPlaceAt(int placeX, int placeY, glm::ivec2 size);
    public:
        ObstaclesGenerator(Map::ObstaclesGrid* grid, std::vector<Map::Obstacle> prefabs, World* world);

        void generate();
    };
}


#endif //PLANETEXHAUSTER_OBSTACLESGENERATOR_H
