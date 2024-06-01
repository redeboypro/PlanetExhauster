//
// Created by redeb on 25.05.2024.
//

#include "Simplex.h"

Simplex& Simplex::operator=(const std::vector<glm::vec3>& vertexList) {
    for (size_t i = 0; i < vertexList.size() && i < 4; ++i) {
        m_vertices[i] = vertexList[i];
        m_size++;
    }
    return *this;
}

void Simplex::push(const glm::vec3& vertex) {
    m_vertices = {
        vertex,
        m_vertices[0],
        m_vertices[1],
        m_vertices[2]
    };
    m_size = std::min(m_size + 1, 4);
}
