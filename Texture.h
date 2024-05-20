//
// Created by redeb on 20.05.2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <cstdint>
#include <vector>
#include <GL/gl.h>

#include "Assert.h"

#define RGBA_TEM_ABS_SIZE (WIDTH * HEIGHT * 4)

struct TexParameter final {
    GLenum name;
    GLenum mode;
};

template<int32_t WIDTH, int32_t HEIGHT>
class TextureRgba final {
    GLuint m_id = 0;
    std::array<uint8_t, RGBA_TEM_ABS_SIZE> m_buffer;

    uint32_t getPixelIndex(const uint32_t x, const uint32_t y) {
        uint32_t index = (y * WIDTH + x) * 4;
        engine_assert((index >= m_buffer.Length - 3), "Invalid pixel coordinates");
        return index;
    }

public:
    TextureRgba() {
        glGenTextures(1, &m_id);

        bind();
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width, height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            m_buffer.data());
    }

    explicit TextureRgba(const std::array<uint8_t, RGBA_TEM_ABS_SIZE> data) :
    TextureRgba() {
        m_buffer = data;
    }

    ~TextureRgba() {
        destroy();
    }

    constexpr static int32_t width = WIDTH;
    constexpr static int32_t height = HEIGHT;
    constexpr static int32_t absoluteSize = RGBA_TEM_ABS_SIZE;

    void bind() const {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void getPixel(
    const uint32_t x,
    const uint32_t y,
    uint8_t& r,
    uint8_t& g,
    uint8_t& b,
    uint8_t& a) {
        uint32_t index = getPixelIndex(x, y);
        r = m_buffer[index];
        g = m_buffer[index + 1];
        b = m_buffer[index + 2];
        a = m_buffer[index + 3];
    }

    void setPixel(
        const uint32_t x,
        const uint32_t y,
        uint8_t r,
        uint8_t g,
        uint8_t b,
        uint8_t a) {
        uint32_t index = getPixelIndex(x, y);
        m_buffer[index] = r;
        m_buffer[index] = g;
        m_buffer[index] = b;
        m_buffer[index] = a;
    }

    void apply() {
        bind();
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0, 0,
            WIDTH, HEIGHT,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            m_buffer.data());
    }

    void destroy() const {
        glDeleteTextures(1, &m_id);
    }
};

#endif //TEXTURE_H
