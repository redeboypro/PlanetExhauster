//
// Created by redeb on 31.05.2024.
//

#ifndef FONT_H
#define FONT_H
#include <unordered_map>
#include <ranges>

#include "../Primitives.h"
#include "../GLAPI.h"

class TextureRgba;

struct FontChar final {
    FontChar(const float left, const float right, const float top, const float bottom) {
        m_vertexArray = new VAO();
        m_vertexArray->bind();

        m_vertexBuffer = new VBO();
        m_vertexBuffer->store(quad_vertices, 8);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);

        m_texCoordBuffer = new VBO();
        m_texCoords[0] = m_texCoords[2] = left;
        m_texCoords[4] = m_texCoords[6] = right;
        m_texCoords[1] = m_texCoords[5] = top;
        m_texCoords[3] = m_texCoords[7] = bottom;
        m_texCoordBuffer->store(m_texCoords, 8);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, nullptr);
    }

    ~FontChar() {
        m_vertexArray->bind();
        delete m_vertexBuffer;
        delete m_texCoordBuffer;
        delete m_vertexArray;
    }

    [[nodiscard]] VAO* getVertexArray() const {
        return m_vertexArray;
    }
private:
    VAO* m_vertexArray;
    VBO* m_vertexBuffer;
    VBO* m_texCoordBuffer;

    GLfloat m_texCoords[8] {};
};

class Font {
    TextureRgba* m_atlasTexture;
    std::unordered_map<char, FontChar*> m_chars;
public:
    explicit Font(TextureRgba* atlasTexture, int32_t charSize);
    ~Font();

    FontChar* getChar(const char sym) {
        return m_chars[sym];
    }

    TextureRgba* getAtlasTexture() const {
        return m_atlasTexture;
    }

    const std::string sheet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()-=_+[]{}\\|;:'\".,<>/?`~ ";
};



#endif //FONT_H
