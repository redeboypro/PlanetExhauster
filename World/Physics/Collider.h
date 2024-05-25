//
// Created by redeb on 25.05.2024.
//

#ifndef COLLIDER_H
#define COLLIDER_H
#include <vec3.hpp>
#include <vector>
#include <detail/func_geometric.inl>

#include "../Entity.h"

struct Collider final {
    [[nodiscard]] glm::vec3 findFurthestPoint(const Entity* entity, const glm::vec3& direction) const;

    [[nodiscard]] size_t size() const {
        return m_vertices.size();
    }

private:
    std::vector<glm::vec3> m_vertices;
};



#endif //COLLIDER_H
