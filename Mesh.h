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
    VAO* m_vertexArray;
    VBO* m_vertexBuffer;
    VBO* m_texCoordBuffer;
    EBO* m_indexBuffer;

    glm::vec3 m_min {FLT_MAX}, m_max {FLT_MAX};
public:
    Mesh() {
        m_vertexArray = new VAO();
        m_vertexArray->bind();
        m_vertexBuffer = new VBO();
        m_texCoordBuffer = new VBO();
        m_indexBuffer = new EBO();
    };
    ~Mesh() {
        m_vertexArray->bind();
        delete m_vertexBuffer;
        delete m_texCoordBuffer;
        delete m_indexBuffer;
        delete m_vertexArray;
    }

    const std::vector<GLfloat>& vertices = m_vertices;
    const std::vector<GLfloat>& texCoords = m_texCoords;
    const std::vector<GLuint>& indices = m_indices;

    const glm::vec3& min = m_min;
    const glm::vec3& max = m_max;

    [[nodiscard]] VAO* getVertexArray() const {
        return m_vertexArray;
    }

    void setVertices(const std::vector<GLfloat>& vertices) {
        m_vertices = vertices;
        m_vertexArray->bind();
        if (!m_vertexBuffer->store(vertices.data(), static_cast<GLsizei>(vertices.size()))) {
            glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
        }

        for (int vi = 0; vi < vertices.size(); vi += 3) {
            const GLfloat& x = vertices[vi];
            const GLfloat& y = vertices[vi + 1];
            const GLfloat& z = vertices[vi + 2];

            m_min.x = std::min(x, m_min.x);
            m_min.y = std::min(y, m_min.y);
            m_min.z = std::min(z, m_min.z);

            m_max.x = std::max(x, m_max.x);
            m_max.y = std::max(y, m_max.y);
            m_max.z = std::max(z, m_max.z);
        }
    }

    void setTexCoords(const std::vector<GLfloat>& texCoords) {
        m_texCoords = texCoords;
        m_vertexArray->bind();
        if (!m_texCoordBuffer->store(texCoords.data(), static_cast<GLsizei>(texCoords.size()))) {
            glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, nullptr);
        }
    }

    void setIndices(const std::vector<GLuint>& indices) {
        m_indices = indices;
        m_vertexArray->bind();
        m_indexBuffer->store(indices.data(), static_cast<GLsizei>(indices.size()));
    }

    static Mesh* cube() {
        const auto mesh = new Mesh();

        GLfloat rawVertices[8][3]{
            {-0.5F, -0.5F, 0.5F},
            {0.5F, -0.5F, 0.5F},
            {0.5F, -0.5F, -0.5F},
            {-0.5F, -0.5F, -0.5F},

            {-0.5F, 0.5F, 0.5F},
            {0.5F, 0.5F, 0.5F},
            {0.5F, 0.5F, -0.5F},
            {-0.5F, 0.5F, -0.5F}
        };

        mesh->setIndices({
            3, 1, 0,        3, 2, 1,
            7, 5, 4,        7, 6, 5,
            11, 9, 8,       11, 10, 9,
            15, 13, 12,     15, 14, 13,
            19, 17, 16,     19, 18, 17,
            23, 21, 20,     23, 22, 21,
        });
        mesh->setVertices({
            rawVertices[0][0], rawVertices[0][1], rawVertices[0][2],
            rawVertices[1][0], rawVertices[1][1], rawVertices[1][2],
            rawVertices[2][0], rawVertices[2][1], rawVertices[2][2],
            rawVertices[3][0], rawVertices[3][1], rawVertices[3][2],
            rawVertices[7][0], rawVertices[7][1], rawVertices[7][2],
            rawVertices[4][0], rawVertices[4][1], rawVertices[4][2],
            rawVertices[0][0], rawVertices[0][1], rawVertices[0][2],
            rawVertices[3][0], rawVertices[3][1], rawVertices[3][2],
            rawVertices[4][0], rawVertices[4][1], rawVertices[4][2],
            rawVertices[5][0], rawVertices[5][1], rawVertices[5][2],
            rawVertices[1][0], rawVertices[1][1], rawVertices[1][2],
            rawVertices[0][0], rawVertices[0][1], rawVertices[0][2],
            rawVertices[6][0], rawVertices[6][1], rawVertices[6][2],
            rawVertices[7][0], rawVertices[7][1], rawVertices[7][2],
            rawVertices[3][0], rawVertices[3][1], rawVertices[3][2],
            rawVertices[2][0], rawVertices[2][1], rawVertices[2][2],
            rawVertices[5][0], rawVertices[5][1], rawVertices[5][2],
            rawVertices[6][0], rawVertices[6][1], rawVertices[6][2],
            rawVertices[2][0], rawVertices[2][1], rawVertices[2][2],
            rawVertices[1][0], rawVertices[1][1], rawVertices[1][2],
            rawVertices[7][0], rawVertices[7][1], rawVertices[7][2],
            rawVertices[6][0], rawVertices[6][1], rawVertices[6][2],
            rawVertices[5][0], rawVertices[5][1], rawVertices[5][2],
            rawVertices[4][0], rawVertices[4][1], rawVertices[4][2]
        });

        GLfloat uv00[2] = {0.0F, 0.0F};
        GLfloat uv10[2] = {1.0F, 0.0F};
        GLfloat uv01[2] = {0.0F, 1.0F};
        GLfloat uv11[2] = {1.0F, 1.0F};

        mesh->setTexCoords({
            uv11[0], uv11[1], uv01[0], uv01[1], uv00[0], uv00[1], uv10[0], uv10[1],
            uv11[0], uv11[1], uv01[0], uv01[1], uv00[0], uv00[1], uv10[0], uv10[1],
            uv11[0], uv11[1], uv01[0], uv01[1], uv00[0], uv00[1], uv10[0], uv10[1],
            uv11[0], uv11[1], uv01[0], uv01[1], uv00[0], uv00[1], uv10[0], uv10[1],
            uv11[0], uv11[1], uv01[0], uv01[1], uv00[0], uv00[1], uv10[0], uv10[1],
            uv11[0], uv11[1], uv01[0], uv01[1], uv00[0], uv00[1], uv10[0], uv10[1]
        });
        glBindVertexArray(0);
        return mesh;
    }
};


#endif //MESH_H
