//
// Created by redeb on 25.05.2024.
//

#ifndef SIMPLEX_H
#define SIMPLEX_H
#include <array>
#include <vec3.hpp>


struct Simplex final {
    Simplex(): m_vertices() {}

    Simplex& operator=(std::initializer_list<glm::vec3> vertexList);
    void push(const glm::vec3& vertex);

    glm::vec3& operator[](const int32_t index) {
        return m_vertices[index];
    }

    [[nodiscard]] size_t size() const {
        return m_size;
    }

    [[nodiscard]] auto begin() const {
        return m_vertices.begin();
    }

    [[nodiscard]] auto end() const {
        return m_vertices.end() - (4 - m_size);
    }

private:
    std::array<glm::vec3, 4> m_vertices;
    int32_t m_size = 0;
};



#endif //SIMPLEX_H
