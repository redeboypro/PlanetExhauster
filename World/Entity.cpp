//
// Created by redeb on 22.05.2024.
//

#include "Entity.h"

void Entity::update(bool isLocal) { // NOLINT(*-no-recursion)
    glm::vec3 tmp_skew;
    glm::vec4 tmp_perspective;

    const glm::mat4 parentMatrix = m_parent != nullptr ?
        m_parent->m_worldMatrix : glm::mat4 ID_MAT4X4;

    while (true) {
        if (isLocal) {
            m_localMatrix = scale(translate(glm::mat4 ID_MAT4X4, m_localPosition) *
                    toMat4(m_localOrientation), m_localScale);

            m_worldMatrix = parentMatrix * m_localMatrix;

            decompose(m_worldMatrix, m_worldScale, m_worldOrientation, m_worldPosition,
                tmp_skew, tmp_perspective);
            m_worldOrientation = conjugate(m_worldOrientation);

            for (const auto child : m_children) {
                child->update(true);
            }
            return;
        }

        glm::mat4 rawMatrix = parentMatrix *
            scale(translate(glm::mat4 ID_MAT4X4, m_worldPosition) *
                    toMat4(m_worldOrientation), m_worldScale);

        decompose(rawMatrix, m_localScale, m_localOrientation, m_localPosition,
            tmp_skew, tmp_perspective);
        m_worldOrientation = conjugate(m_worldOrientation);

        isLocal = true;
    }
}

Entity::Entity() {
    update(true);
}

Entity::~Entity() {
    for (const auto& childIndex : m_children) {
        childIndex->setParent(nullptr, true);
    }
}

void Entity::setParent(Entity* parent, bool worldTransformStays) { // NOLINT(*-no-recursion)
    if (m_parent != parent) {
        m_parent->removeChild(this);
    }

    const auto worldPosition = m_worldPosition;
    const auto worldOrientation = m_worldOrientation;
    const auto worldScale = m_worldScale;

    m_parent = parent;
    update(true);

    if (worldTransformStays) {
        m_worldPosition = worldPosition;
        m_worldOrientation = worldOrientation;
        m_worldScale = worldScale;
        update(false);
    }

    m_parent->addChild(this);
}

void Entity::addChild(Entity* child) { // NOLINT(*-no-recursion)
    if (std::ranges::find(m_children, child) != m_children.end()) return;
    m_children.push_back(child);
    child->setParent(this, true);
}

void Entity::removeChild(Entity *child) { // NOLINT(*-no-recursion)
    const auto childIt = std::ranges::find(m_children, child);
    if (childIt == m_children.end()) return;
    m_children.erase(childIt);
    child->setParent(nullptr, true);
}


