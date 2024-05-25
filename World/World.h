//
// Created by redeb on 25.05.2024.
//

#ifndef WORLD_H
#define WORLD_H
#include "Entity.h"
#include "../Mesh.h"
#include "../Texture.h"

struct World final {
    World();

    Entity* instantiate();

    void update();

private:
    std::vector<Entity*> m_entities;
    Entity* m_camera;
};



#endif //WORLD_H
