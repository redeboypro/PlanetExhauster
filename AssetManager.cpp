//
// Created by redeb on 28.05.2024.
//

#include "AssetManager.h"

#include <iostream>

char* AssetManager::readBuffer(const std::string &fileName) {
    std::ifstream inputStream(fileName, std::ios::binary);
    if (!inputStream) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return nullptr;
    }

    inputStream.seekg(0, std::ios::end);
    const long long size = inputStream.tellg();
    inputStream.seekg(0, std::ios::beg);

    // ReSharper disable once CppDFAMemoryLeak
    const auto buffer = new char[size];
    inputStream.read(buffer, static_cast<int32_t>(size));

    inputStream.close();

    return buffer;
}

AssetManager::~AssetManager() {
    for (const auto mesh: m_meshes) {
        delete mesh;
    }

    for (const auto tex: m_textures) {
        delete tex;
    }
}

Mesh* AssetManager::loadMesh(const std::string& fileName) {
    int32_t ptr = 0;
    char* buffer = readBuffer(fileName);
    const int32_t vertexCount = readi(buffer, ptr);
    const int32_t indexCount = readi(buffer, ptr);
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> texCoordinates;
    std::vector<GLuint> indices;

    for (int i = 0; i < vertexCount * 3; ++i) {
        vertices.push_back(readf(buffer, ptr));
    }

    for (int i = 0; i < vertexCount * 2; ++i) {
        texCoordinates.push_back(readf(buffer, ptr));
    }

    for (int i = 0; i < indexCount; ++i) {
        indices.push_back(readui(buffer, ptr));
    }

    auto* mesh = new Mesh();
    mesh->setVertices(vertices);
    mesh->setTexCoords(texCoordinates);
    mesh->setIndices(indices);
    m_meshes.push_back(mesh);

    delete[] buffer;

    return mesh;
}

TextureRgba* AssetManager::loadTexture(const std::string& fileName, const std::initializer_list<TexParameter> parameters) {
    int32_t ptr = 0;
    char* buffer = readBuffer(fileName);

    const int32_t width = readi(buffer, ptr);
    const int32_t height = readi(buffer, ptr);
    const int32_t stride = readi(buffer, ptr);

    std::vector<uint8_t> pixelBuffer;

    for (int i = 0; i < stride * height; ++i) {
        pixelBuffer.push_back(readuc(buffer, ptr));
    }

    auto* texture = new TextureRgba(width, height, pixelBuffer, parameters);
    m_textures.push_back(texture);

    delete[] buffer;

    return texture;
}
