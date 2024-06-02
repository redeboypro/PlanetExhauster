//
// Created by probn on 01.06.2024.
//

#ifndef PLANETEXHAUSTER_OBSTACLE_H
#define PLANETEXHAUSTER_OBSTACLE_H

#include <vec2.hpp>

#include "../../World/Entity.h"
#include "../../World/Physics/Collider.h"
#include "../../World/Physics/Rigidbody.h"
#include "../../World/World.h"

namespace Map
{
    class Obstacle
    {
        Entity *m_entity;
        Rigidbody *m_rigidbody;
        Collider *m_collider;

        glm::ivec2 m_size;
        int m_maxCount;

    public:
        Obstacle(const glm::ivec2 &size, int maxCount, Mesh *mesh, World *world);
        ~Obstacle();

        [[nodiscard]] const glm::ivec2 &getSize() const {
            return m_size;
        }

        [[nodiscard]] int getMaxCount() const {
            return m_maxCount;
        }

        [[nodiscard]] Rigidbody *getRigidbody() const {
            return m_rigidbody;
        }

        [[nodiscard]] Entity *getEntity() const {
            return m_entity;
        }
    };
}


#endif //PLANETEXHAUSTER_OBSTACLE_H
