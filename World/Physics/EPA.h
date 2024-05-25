//
// Created by redeb on 25.05.2024.
//

#ifndef EPA_H
#define EPA_H
#include <algorithm>
#include <cfloat>

#include "Collider.h"
#include "Collision.h"
#include "GJK.h"
#include "Simplex.h"

#define EPS 0.0001F

namespace EPA {
    Collision epa(const Simplex& simplex, const EntityCollision& objA, const EntityCollision& objB);
    std::vector<CollisionNormal> getFaceNormals(
        const std::vector<glm::vec3> &polytope,
        const std::vector<size_t> &faces,
        int32_t& minTriangle);

    void addIfUniqueEdge(
        std::vector<std::pair<size_t, size_t>>& edges,
        const std::vector<size_t>& faces,
        size_t a,
        size_t b);
}

#endif //EPA_H
