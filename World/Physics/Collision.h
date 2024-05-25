//
// Created by redeb on 25.05.2024.
//

#ifndef COLLISION_H
#define COLLISION_H
#include <vec3.hpp>

struct Collision final {
    glm::vec3 normal;
    float penetrationDepth;
};

struct CollisionNormal final {
    glm::vec3 direction;
    float distance;
};

#endif //COLLISION_H
