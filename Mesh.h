//
// Created by redeb on 16.05.2024.
//

#ifndef MESH_H
#define MESH_H
#include "GLAPI.h"

class Mesh final {
    std::vector<GLfloat> m_vertices;
    std::vector<GLfloat> m_texCoords;
    std::vector<GLuint> m_indices;
    VAO m_vertexArray;
    VBO m_vertexBuffer;
    VBO m_texCoordBuffer;
    EBO m_indexBuffer;
public:
    Mesh() = default;
    ~Mesh() {
        m_vertexArray.bind();
        m_vertexBuffer.destroy();
        m_texCoordBuffer.destroy();
        m_indexBuffer.destroy();
        m_vertexArray.destroy();
    }

    const std::vector<GLfloat>& vertices = m_vertices;
    const std::vector<GLfloat>& texCoords = m_texCoords;
    const std::vector<GLuint>& indices = m_indices;

    void setVertices(const std::vector<GLfloat>& vertices) {
        m_vertices = vertices;
        m_vertexArray.bind();
        m_vertexBuffer.store(vertices.data(), static_cast<GLsizei>(vertices.size()));
    }

    void setTexCoords(const std::vector<GLfloat>& texCoords) {
        m_texCoords = texCoords;
        m_vertexArray.bind();
        m_texCoordBuffer.store(texCoords.data(), static_cast<GLsizei>(texCoords.size()));
    }

    void setIndices(const std::vector<GLuint>& indices) {
        m_indices = indices;
        m_vertexArray.bind();
        m_indexBuffer.store(indices.data(), static_cast<GLsizei>(indices.size()));
    }
};


#endif //MESH_H
