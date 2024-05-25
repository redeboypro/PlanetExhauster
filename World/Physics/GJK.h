//
// Created by redeb on 25.05.2024.
//

#ifndef GJK_H
#define GJK_H
#include <vec3.hpp>

#include "Collider.h"
#include "Simplex.h"


namespace GJK {
    glm::vec3 supportPoint(const Collider& colliderA, const Collider& colliderB, const glm::vec3 &direction);
    bool gjk(const Collider& colliderA, const Collider& colliderB);
    bool nextSimplex(Simplex& simplex, glm::vec3& direction);
    bool sameDirection(const glm::vec3& direction, const glm::vec3& ao);
    bool line(Simplex& simplex, glm::vec3& direction);
    bool triangle(Simplex& simplex, glm::vec3& direction);
    bool tetrahedron(Simplex& simplex, glm::vec3& direction);
}


#endif //GJK_H
