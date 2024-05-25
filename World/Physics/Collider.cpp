//
// Created by redeb on 25.05.2024.
//

#include "Collider.h"

#include <cfloat>

glm::vec3 Collider::findFurthestPoint(const Entity* entity, const glm::vec3& direction) const {
    glm::vec3 maxPoint = m_vertices[m_vertices.size() - 1];
    float maxDistance = -FLT_MAX;

    for (const auto& vertex : m_vertices) {
        auto transformedVertex = entity->getWorldOrientation() * (vertex * entity->getWorldScale());
        if (const float distance = dot(transformedVertex, direction); distance > maxDistance) {
            maxDistance = distance;
            maxPoint = transformedVertex;
        }
    }

    return maxPoint + entity->getWorldPosition();
}
