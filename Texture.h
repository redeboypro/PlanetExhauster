//
// Created by redeb on 20.05.2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <cstdint>
#include <vector>
#include <GL/gl.h>

#include "Assert.h"
#include "GLAPI.h"

#define RGBA_TEM_ABS_SIZE (WIDTH * HEIGHT * 4)

struct TexParameter final {
    GLenum name;
    GLint mode;
};

class TextureRgba final {
    GLuint m_id = 0;
    std::vector<uint8_t> m_buffer;

    [[nodiscard]] uint32_t getPixelIndex(const uint32_t x, const uint32_t y) const {
        const uint32_t index = (y * width + x) * 4;
        engine_assert((index >= m_buffer.size() - 3), "Invalid pixel coordinates");
        return index;
    }

public:
    TextureRgba(
        const int32_t width,
        const int32_t height,
        std::initializer_list<TexParameter> parameters) :
    width(width),
    height(height) {
        glGenTextures(1, &m_id);
        bind();

        for (const auto [name, mode] : parameters) {
            glTexParameteri(GL_TEXTURE_2D, name, mode);
        }

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            width, height,
            0,
            0x80E1,
            GL_UNSIGNED_BYTE,
            nullptr);
    }

    TextureRgba(
        const int32_t width,
        const int32_t height,
        const std::vector<uint8_t>& data,
        const std::initializer_list<TexParameter> parameters) :
    TextureRgba(width, height, parameters) {
        m_buffer = data;
        apply();
    }

    ~TextureRgba() {
        destroy();
    }

    const int32_t width = 0, height = 0;

    void bind() const {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void getPixel(
    const uint32_t x,
    const uint32_t y,
    uint8_t& r,
    uint8_t& g,
    uint8_t& b,
    uint8_t& a) const {
        const uint32_t index = getPixelIndex(x, y);
        r = m_buffer[index];
        g = m_buffer[index + 1];
        b = m_buffer[index + 2];
        a = m_buffer[index + 3];
    }

    void setPixel(
        const uint32_t x,
        const uint32_t y,
        const uint8_t r,
        const uint8_t g,
        const uint8_t b,
        const uint8_t a) {
        const uint32_t index = getPixelIndex(x, y);
        m_buffer[index] = r;
        m_buffer[index] = g;
        m_buffer[index] = b;
        m_buffer[index] = a;
    }

    void apply() const {
        bind();
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0, 0,
            width, height,
            0x80E1,
            GL_UNSIGNED_BYTE,
            m_buffer.data());
    }

    void destroy() const {
        glDeleteTextures(1, &m_id);
    }

    TextureRgba& operator=(const std::vector<uint8_t>& buffer) {
        m_buffer = buffer;
        apply();
        return *this;
    }

    static void active(const uint32_t texture) {
        glActiveTexture(33984 + texture);
    }
};

#endif //TEXTURE_H
