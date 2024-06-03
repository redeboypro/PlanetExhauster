//
// Created by redeb on 25.05.2024.
//

#include "World.h"

World::World(
    const float fov,
    const float aspect,
    const float cameraNear, const float cameraFar) :
m_shader(nullptr),
m_projectionMatrix(glm::perspective(
    fov,
    aspect,
    cameraNear, cameraFar)) {
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glCullFace(GL_BACK);
    m_camera = new Rigidbody(true);
    instantiate(m_camera, defaultLayer);
}

World::~World() {
    for (const auto& layer : std::ranges::views::values(m_layers)) {
        for (const Rigidbody* rigidbody : layer) {
            delete rigidbody;
        }
    }
    delete m_shader;
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
    if (!m_shader) return;
    m_shader->use();
    for (const auto& layerTitle: m_layersOrder) {
        auto& layer = m_layers[layerTitle];
        glClear(GL_DEPTH_BUFFER_BIT);
        for (const auto rigidbody : layer) {
            const auto* entity = rigidbody->getEntity();
            const auto color = entity->getColor();
            const auto* texture = entity->getTexture();

            const auto* mesh = entity->getMesh();
            if (!mesh or !entity->active()) continue;

            m_shader->uniform1i(glHasTextureUniform, texture != nullptr);
            m_shader->uniform4f(glColorUniform, color.r, color.g, color.b, color.a);

            const auto* cameraEnt = m_camera->getEntity();

            m_shader->uniformMatrix4fv(glViewMatrixUniform, value_ptr(inverse(cameraEnt->getWorldMatrix())), false);
            m_shader->uniformMatrix4fv(glProjectionMatrixUniform, value_ptr(m_projectionMatrix), false);
            m_shader->uniformMatrix4fv(glModelMatrixUniform, value_ptr(entity->getWorldMatrix()), false);

            if (texture) {
                TextureRgba::active(0);
                texture->bind();
            }

            mesh->getVertexArray()->bind();

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->indices.size()), GL_UNSIGNED_INT, nullptr);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);

            glBindVertexArray(0);
        }
    }
}
