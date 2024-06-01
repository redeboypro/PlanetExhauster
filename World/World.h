//
// Created by redeb on 25.05.2024.
//

#ifndef WORLD_H
#define WORLD_H
#include <unordered_map>
#include <gtc/type_ptr.hpp>

#include <ranges>
#include "Entity.h"
#include "../Shader.h"
#include "../Texture.h"
#include "Physics/Rigidbody.h"

struct World final {
    World(
        float fov,
        float aspect,
        float cameraNear, float cameraFar);

    ~World();

    constexpr static std::string defaultLayer = "Default";

    Shader* getShader() const {
        return m_shader;
    }

    void setShader(Shader* shader) {
        m_shader = shader;
    }

    Rigidbody* getCamera() const {
        return m_camera;
    };

    void instantiate(Rigidbody* rigidbody, const std::string& layer);
    Rigidbody* instantiate(const std::string& layer);

    void setLayersOrder(std::initializer_list<std::string> layersOrder);

    void update(float deltaTime);
    void render();

private:
    Shader* m_shader;

    Rigidbody* m_camera;
    glm::mat4 m_projectionMatrix;

    std::unordered_map<std::string, std::vector<Rigidbody*>> m_layers;
    std::vector<std::string> m_layersOrder;
};



#endif //WORLD_H
