//
// Created by redeb on 31.05.2024.
//

#ifndef GUI_H
#define GUI_H

#include <vec2.hpp>
#include <ext/matrix_transform.hpp>

#include "Font.h"
#include "../Input.h"
#include "../Shader.h"
#include "../Window.h"

#define glGuiTransformMatrix "transform_matrix"

class GUI final {
    Font* m_font = nullptr;
    Shader* m_shader;
    Input* m_input;

    Window* m_window;

    VAO* m_quadVertexArray;
    VBO* m_quadVertexBuffer;
    VBO* m_quadTexCoordBuffer;

    void screenToViewport(GLint x, GLint y, GLfloat& xv, GLfloat& yv) const;
public:
    explicit GUI(Shader* shader, Input* input, Window* window) :
    m_shader(shader), m_input(input), m_window(window) {
        m_quadVertexArray = new VAO();
        m_quadVertexArray->bind();

        m_quadVertexBuffer = new VBO();
        m_quadVertexBuffer->store(quad_vertices, 8);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);

        m_quadTexCoordBuffer = new VBO();
        m_quadTexCoordBuffer->store(quad_uv, 8);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, nullptr);
    }

    ~GUI() {
        delete m_font;
        delete m_shader;

        m_quadVertexArray->bind();
        delete m_quadVertexBuffer;
        delete m_quadTexCoordBuffer;
        delete m_quadVertexArray;
    }

    void label(const std::string& text, const glm::vec2& position, const glm::vec2& scaleDim) const;
    void img(const TextureRgba* texture, const glm::vec2& position, const glm::vec2& scaleDim) const;
    [[nodiscard]] bool button(const TextureRgba* texture, const glm::vec2& position, const glm::vec2& scaleDim) const;
};



#endif //GUI_H
