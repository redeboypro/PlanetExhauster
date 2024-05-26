//
// Created by redeb on 25.05.2024.
//

#ifndef WORLD_H
#define WORLD_H
#include <unordered_map>

#include <ranges>
#include "Entity.h"
#include "../Mesh.h"
#include "../Texture.h"
#include "Physics/Rigidbody.h"

struct World final {
    World();
    ~World();

    void instantiate(Rigidbody* rigidbody, const std::string& layer);
    Rigidbody* instantiate(const std::string& layer);

    void setLayersOrder(std::initializer_list<std::string> layersOrder);

    void update(float deltaTime);
    void render();

private:
    Rigidbody* m_camera;
    std::unordered_map<std::string, std::vector<Rigidbody*>> m_layers;
    std::vector<std::string> m_layersOrder;
};



#endif //WORLD_H
