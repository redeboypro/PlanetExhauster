//
// Created by redeb on 31.05.2024.
//

#include "Font.h"

Font::Font(TextureRgba* atlasTexture, const int32_t charSize) : m_atlasTexture(atlasTexture) {
    const float absoluteCharSize = 1.0F / static_cast<float>(charSize);
    for (const auto sym : sheet) {
        const int32_t y = sym >> 4;
        const int32_t x = sym & 0b1111;

        const float left = static_cast<float>(x) * absoluteCharSize;
        const float right = left + absoluteCharSize;

        const float top = static_cast<float>(y) * absoluteCharSize;
        const float bottom = top + absoluteCharSize;

        m_chars[sym] = new FontChar(left, right, top, bottom);
    }
}

Font::~Font() {
    for (const auto charData : std::ranges::views::values(m_chars)) {
        delete charData;
    }
}
