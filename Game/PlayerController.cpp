//
// Created by redeb on 01.06.2024.
//

#include "PlayerController.h"

void PlayerController::move(const glm::vec3 &vec) const {
    m_playerEnt->setLocalPosition(m_playerEnt->getLocalPosition() + vec);
}

PlayerController::PlayerController(World* world, Input* input) : m_input(input), m_pitch(0.0F), m_yaw(0.0F) {
    m_player = world->instantiate(World::defaultLayer);
    m_collider = new Collider(glm::vec3 {-PLAYER_SIZE}, glm::vec3 {PLAYER_SIZE});
    m_player->setCollisionShapes({m_collider});
    m_playerEnt = m_player->getEntity();

    m_cameraEnt = world->getCamera()->getEntity();
    m_cameraEnt->setParent(m_playerEnt);
    m_player->isKinematic = false;
}

PlayerController::~PlayerController() {
    delete m_collider;
}

Rigidbody* PlayerController::getRigidbody() const {
    return m_player;
}

void PlayerController::update(const GLfloat deltaTime) {
    const GLfloat absoluteSpeed = deltaTime * PLAYER_SPEED;

    const auto acceleratedForward = m_playerEnt->forward() * absoluteSpeed;
    const auto acceleratedRight = m_playerEnt->right() * absoluteSpeed;

    if (m_input->getKey(KeyCode::W)) {
        move(acceleratedForward);
    }

    if (m_input->getKey(KeyCode::S)) {
        move(-acceleratedForward);
    }

    if (m_input->getKey(KeyCode::A)) {
        move(acceleratedRight);
    }

    if (m_input->getKey(KeyCode::D)) {
        move(-acceleratedRight);
    }

    if (m_input->getKeyDown(KeyCode::Space) && m_player->grounded()) {
        m_player->tossUp(10);
    }

    const GLfloat rotationSpeed = deltaTime * CAMERA_SPEED;
    m_yaw -= static_cast<GLfloat>(m_input->getDeltaMousePositionX()) * rotationSpeed;
    m_pitch -= static_cast<GLfloat>(m_input->getDeltaMousePositionY()) * rotationSpeed;
    m_pitch = CLAMP(m_pitch, CAMERA_PITCH_MIN, CAMERA_PITCH_MAX);

    m_playerEnt->setLocalOrientation(glm::quat(glm::vec3 {0, glm::radians(m_yaw), 0}));
    m_cameraEnt->setLocalOrientation(glm::quat(glm::vec3 {glm::radians(m_pitch), 0, 0}));
}
