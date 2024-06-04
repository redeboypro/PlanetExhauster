//
// Created by redeb on 25.05.2024.
//

#ifndef COLLIDER_H
#define COLLIDER_H

#include <vector>
#include <cfloat>

#include "../Entity.h"

struct Collider final
{
    Collider(const glm::vec3 &min, const glm::vec3 &max) : m_vertices({
                                                                              glm::vec3(min.x, min.y, min.z),
                                                                              glm::vec3(min.x, max.y, min.z),
                                                                              glm::vec3(max.x, min.y, min.z),
                                                                              glm::vec3(max.x, max.y, min.z),

                                                                              glm::vec3(min.x, min.y, max.z),
                                                                              glm::vec3(min.x, max.y, max.z),
                                                                              glm::vec3(max.x, min.y, max.z),
                                                                              glm::vec3(max.x, max.y, max.z),
                                                                      }) {}

    explicit Collider(const std::vector<glm::vec3> &vertices) : m_vertices(vertices) {}

    explicit Collider(const Mesh *mesh);

    [[nodiscard]] glm::vec3 findFurthestPoint(const Entity *entity, const glm::vec3 &direction) const;

    [[nodiscard]] size_t size() const {
        return m_vertices.size();
    }

private:
    std::vector<glm::vec3> m_vertices;
};


#endif //COLLIDER_H