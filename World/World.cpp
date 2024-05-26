//
// Created by redeb on 25.05.2024.
//

#include "World.h"

#include "Physics/Rigidbody.h"

World::World() {
    m_camera = new Rigidbody(true);
}

World::~World() {
    for (const auto& layer : std::ranges::views::values(m_layers)) {
        for (const Rigidbody* rigidbody : layer) {
            delete rigidbody;
        }
    }
}

void World::instantiate(Rigidbody *rigidbody, const std::string &layer) {
    if (!m_layers.contains(layer)) {
        m_layers[layer] = std::vector<Rigidbody*>();
    }

    if (std::ranges::find(m_layersOrder, layer) ==
        m_layersOrder.end()) {
        m_layersOrder.push_back(layer);
    }

    m_layers[layer].push_back(rigidbody);
}

Rigidbody* World::instantiate(const std::string &layer) {
    auto* rigidbody = new Rigidbody(false);
    instantiate(rigidbody, layer);
    return rigidbody;
}

void World::setLayersOrder(const std::initializer_list<std::string> layersOrder) {
    for (const auto& layer: layersOrder) {
        if (!m_layers.contains(layer)) {
            m_layers[layer] = std::vector<Rigidbody*>();
        }
    }
    m_layersOrder = layersOrder;
}

void World::update(const float deltaTime) {
    int32_t layerAIndex = 0;
    for (auto &layerA: m_layers | std::views::values) {
        for (int32_t indexA = 0; indexA < layerA.size(); ++indexA) {
            auto* rigidbodyA = layerA[indexA];
            auto* entityA = rigidbodyA->getEntity();

            if (!entityA->active() or
                rigidbodyA->isKinematic or
                rigidbodyA->isTrigger) continue;

            rigidbodyA->accelerateFall(deltaTime);
            entityA->setLocalPosition(entityA->getLocalPosition() +
                glm::vec3 {0, rigidbodyA->getFallVelocity() * deltaTime, 0});

            std::vector<Rigidbody*> triggers;
            std::vector<Response> responses;

            int32_t layerBIndex = 0;
            for (auto layerB: m_layers | std::views::values) {
                for (int32_t indexB = 0; indexB < layerB.size(); ++indexB) {
                    auto* rigidbodyB = layerB[indexB];
                    if (const auto* entityB = rigidbodyB->getEntity();
                        (indexA == indexB and layerAIndex == layerBIndex) or
                        !entityB->active() or
                        rigidbodyA->ignoresTag(entityB->getTag()) or
                        rigidbodyB->ignoresTag(entityA->getTag())) {
                        continue;
                    }
                    rigidbodyA->resolveCollision(rigidbodyB, triggers, responses);
                }
                layerBIndex++;
            }

            rigidbodyA->refreshTriggers(triggers);
            rigidbodyA->refreshResponses(responses);
        }
        layerAIndex++;
    }
}

void World::render() {

}
