//
// Created by redeb on 25.05.2024.
//

#include "Collider.h"

Collider::Collider(const glm::vec3 &min, const glm::vec3 &max) {
    setVertices(min, max);
}

Collider::Collider(const Mesh* mesh) {
    const auto& vertices = mesh->vertices;
    for (size_t i = 0; i < vertices.size(); i += 3) {
        m_vertices.emplace_back(vertices[i], vertices[i + 1], vertices[i + 2]);
    }
}

void Collider::setVertices(const std::vector<glm::vec3> &vertices) {
    m_vertices = vertices;
}

void Collider::setVertices(const glm::vec3 &min, const glm::vec3 &max) {
    m_vertices = {
        glm::vec3(min.x, min.y, min.z),
        glm::vec3(min.x, max.y, min.z),
        glm::vec3(max.x, min.y, min.z),
        glm::vec3(max.x, max.y, min.z),

        glm::vec3(min.x, min.y, max.z),
        glm::vec3(min.x, max.y, max.z),
        glm::vec3(max.x, min.y, max.z),
        glm::vec3(max.x, max.y, max.z),
    };
}

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
