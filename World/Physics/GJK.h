//
// Created by redeb on 25.05.2024.
//

#ifndef GJK_H
#define GJK_H
#include <vec3.hpp>

#include "Collider.h"
#include "Rigidbody.h"
#include "Simplex.h"

struct EntityCollision final {
    Entity* entity;
    Collider* collider;
};

namespace GJK {
    glm::vec3 supportPoint(const EntityCollision& objA, const EntityCollision& objB, const glm::vec3 &direction);
    bool gjk(const EntityCollision& objA, const EntityCollision& objB, Simplex& simplex);
    bool nextSimplex(Simplex& simplex, glm::vec3& direction);
    bool sameDirection(const glm::vec3& direction, const glm::vec3& ao);
    bool line(Simplex& simplex, glm::vec3& direction);
    bool triangle(Simplex& simplex, glm::vec3& direction);
    bool tetrahedron(Simplex& simplex, glm::vec3& direction);
}


#endif //GJK_H
