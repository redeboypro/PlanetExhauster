//
// Created by redeb on 03.06.2024.
//

#include "DinoActor.h"

DinoActor::DinoActor(World* world) : m_dino(world->instantiate(World::defaultLayer)), m_angle(.0F) {
    m_dinoEnt = m_dino->getEntity();
}

DinoActor::~DinoActor() {
    delete m_collider;
}

Entity* DinoActor::getEntity() const {
    return m_dinoEnt;
}

void DinoActor::setModelData(Mesh* mesh, TextureRgba* texture) {
    m_dinoEnt->setMesh(mesh);
    m_dinoEnt->setTexture(texture);
    if (!m_collider) {
        m_collider = new Collider(glm::vec3 {-1, -2, -1}, glm::vec3 {1, 2, 1});
        m_dino->setCollisionShapes({m_collider});
        m_dino->setFallAcceleration(30);
        m_dino->isKinematic = false;
        return;
    }
    m_collider->setVertices(mesh->min, mesh->max);
}

void DinoActor::setTarget(Rigidbody* target) {
    m_target = target;
    m_targetEnt = target->getEntity();
}

void DinoActor::update(const GLfloat deltaTime) const {
    if (!m_targetEnt) {
        return;
    }

    if (m_dino->grounded())
        m_dino->tossUp(DINO_JUMP_FORCE);

    const auto direction = m_targetEnt->getWorldPosition() - m_dinoEnt->getWorldPosition();
    const GLfloat angle = glm::degrees(std::atan2(direction.x, direction.z)) - 90.0F;

    m_dinoEnt->setLocalOrientation(slerp(
        m_dinoEnt->getLocalOrientation(),
        glm::quat(glm::vec3 {0, glm::radians(angle), 0}), deltaTime * DINO_ROTATION_SPEED));
    m_dinoEnt->setLocalPosition(m_dinoEnt->getLocalPosition() - m_dinoEnt->right() * DINO_SPEED * deltaTime);
}
