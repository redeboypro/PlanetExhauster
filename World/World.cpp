//
// Created by redeb on 25.05.2024.
//

#include "World.h"

World::World() {
    m_camera = new Entity(true);
}

Entity* World::instantiate() {
    auto* instance = new Entity(false);
    m_entities.push_back(instance);
    return instance;
}

void World::update() {

}
