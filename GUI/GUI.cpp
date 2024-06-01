//
// Created by redeb on 31.05.2024.
//

#include "GUI.h"

#include "../Texture.h"

void GUI::screenToViewport(const GLint x, const GLint y, GLfloat &xv, GLfloat &yv) const {
    xv = 2.0f * F32(x) / F32(m_window->width) - 1;
    yv = -(2.0f * F32(y) / F32(m_window->height) - 1);
}

void GUI::label(const std::string& text, const glm::vec2& position, const glm::vec2& scaleDim) const {
    if (!m_font) return;

    const GLfloat charWidth = scaleDim.x / static_cast<float>(text.length());
    GLfloat offset = position.x - scaleDim.x + charWidth / 2.0F;
    m_font->getAtlasTexture()->bind();

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    for (const auto sym : text) {
        if (!text.contains(sym)) continue;
        glm::mat4 transform = scale(translate(
            glm::identity<glm::mat4>(),
            {
                offset,
                position.y,
                0
            }),
            {
                charWidth,
                scaleDim.y,
                1
            });
        offset += charWidth;

        m_shader->uniformMatrix4fv(glGuiTransformMatrix, value_ptr(transform), false);

        m_font->getChar(sym)->getVertexArray()->bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void GUI::img(const TextureRgba *texture, const glm::vec2 &position, const glm::vec2 &scaleDim) const {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    texture->bind();

    glm::mat4 transform = scale(translate(
            glm::identity<glm::mat4>(),
            {
                position.x,
                position.y,
                0
            }),
            {
                scaleDim.x,
                scaleDim.y,
                1
            });

    m_shader->uniformMatrix4fv(glGuiTransformMatrix, value_ptr(transform), false);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

bool GUI::button(const TextureRgba* texture, const glm::vec2& position, const glm::vec2& scaleDim) const {
    img(texture, position, scaleDim);

    GLfloat pointX, pointY;
    screenToViewport(
        m_input->getMousePositionX(),
        m_input->getMousePositionY(),
        pointX, pointY);

    const glm::vec2 halfScale = scaleDim * 0.5F;

    return m_input->getKeyDown(KeyCode::MouseLeft) &&
        pointX <= position.x + halfScale.x && pointX >= position.x - halfScale.x &&
        pointX <= position.y + halfScale.y && pointX >= position.y - halfScale.y;
}
