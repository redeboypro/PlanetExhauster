//
// Created by redeb on 25.05.2024.
//

#include "Simplex.h"

Simplex& Simplex::operator=(const std::initializer_list<glm::vec3> vertexList) {
    for (const glm::vec3& vertex : vertexList)
        m_vertices[m_size++] = vertex;

    return *this;
}

void Simplex::push(const glm::vec3 &vertex) {
    m_vertices = {
        vertex,
        m_vertices[0],
        m_vertices[1],
        m_vertices[2]
    };
    m_size = std::min(m_size + 1, 4);
}
