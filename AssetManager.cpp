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
    for (const auto col: m_colliders) {
        delete col;
    }

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

    for (int32_t i = 0; i < vertexCount * 3; ++i) {
        vertices.push_back(readf(buffer, ptr));
    }

    for (int32_t i = 0; i < vertexCount * 2; ++i) {
        texCoordinates.push_back(readf(buffer, ptr));
    }

    for (int32_t i = 0; i < indexCount; ++i) {
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

    for (int32_t i = 0; i < stride * height; ++i) {
        pixelBuffer.push_back(readuc(buffer, ptr));
    }

    auto* texture = new TextureRgba(width, height, pixelBuffer, parameters);
    m_textures.push_back(texture);

    delete[] buffer;

    return texture;
}

std::vector<Collider*> AssetManager::loadCollision(const std::string &fileName) {
    int32_t ptr = 0;
    char* buffer = readBuffer(fileName);

    const int32_t meshCount = readi(buffer, ptr);
    std::vector<Collider*> colliders;

    for (int mi = 0; mi < meshCount; ++mi) {
        std::vector<glm::vec3> vertices;
        const int32_t vertexCount = readi(buffer, ptr);
        for (int32_t vi = 0; vi < vertexCount * 3; vi += 3) {
            vertices.emplace_back(
                    readf(buffer, ptr),
                    readf(buffer, ptr),
                    readf(buffer, ptr));
        }
        auto* collider = new Collider(vertices);
        m_colliders.push_back(collider);
        colliders.push_back(collider);
    }

    delete[] buffer;

    return colliders;
}

void AssetManager::addExternal(Mesh* mesh) {
    m_meshes.push_back(mesh);
}

void AssetManager::addExternal(TextureRgba* texture) {
    m_textures.push_back(texture);
}

void AssetManager::addExternal(Collider* collider) {
    m_colliders.push_back(collider);
}
