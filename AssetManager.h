//
// Created by redeb on 28.05.2024.
//

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include "World/Physics/Collider.h"

class AssetManager {
    std::vector<Mesh*> m_meshes;
    std::vector<TextureRgba*> m_textures;
    std::vector<Collider*> m_colliders;

    static char* readBuffer(const std::string& fileName);

    static uint8_t readuc(char* buffer, int32_t& ptr) {
        return buffer[ptr++];
    }

    static int32_t readi(char* buffer, int32_t& ptr) {
        const int32_t i32 = *reinterpret_cast<int32_t*>(&buffer[ptr]);
        ptr += 4;
        return i32;
    }

    static uint32_t readui(char* buffer, int32_t& ptr) {
        const uint32_t u32 = *reinterpret_cast<uint32_t*>(&buffer[ptr]);
        ptr += 4;
        return u32;
    }

    static float readf(char* buffer, int32_t& ptr) {
        const float f32 = *reinterpret_cast<float*>(&buffer[ptr]);
        ptr += 4;
        return f32;
    }

public:
    AssetManager() = default;
    ~AssetManager();

    Mesh* loadMesh(const std::string& fileName);
    TextureRgba* loadTexture(const std::string& fileName, std::initializer_list<TexParameter> parameters);
    std::vector<Collider*> loadCollision(const std::string& fileName);

    void addExternal(Mesh* mesh);
    void addExternal(TextureRgba* texture);
    void addExternal(Collider* collider);
};



#endif //ASSETMANAGER_H