//
// Created by probn on 01.06.2024.
//

#ifndef PLANETEXHAUSTER_OBSTACLESGRID_H
#define PLANETEXHAUSTER_OBSTACLESGRID_H

#include "../../World/Entity.h"
#include "../../World/Physics/Rigidbody.h"
#include "Obstacle.h"
#include "../../World/World.h"

static const float OBSTACLE_Y_OFFSET = -1;
static const float OBSTACLE_XZ_OFFSET = 5;

namespace Map
{
    class ObstaclesGrid
    {
        World* m_world;
        Entity *m_entity;
        Rigidbody *m_rigidbody;

        glm::ivec2 m_size;
        std::vector<std::vector<bool>> m_grid;

    public:
        ObstaclesGrid(Entity *entity, Rigidbody *rigidbody, const glm::ivec2 &size, World *world);

        void add(const Map::Obstacle &obstacle, int x, int y);

        bool hasAt(int x, int y);

        [[nodiscard]] const glm::ivec2 &getSize() const {
            return m_size;
        }
    };
}

#endif //PLANETEXHAUSTER_OBSTACLESGRID_H
