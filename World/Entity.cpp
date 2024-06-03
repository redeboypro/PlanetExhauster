//
// Created by redeb on 22.05.2024.
//

#include "Entity.h"

void Entity::update() { // NOLINT(*-no-recursion)
    m_localMatrix = scale(translate(m_localPosition) *
                          toMat4(m_localOrientation), m_localScale);

    if (m_parent) {
        const glm::mat4 parentMatrix = m_parent->m_worldMatrix;
        m_worldMatrix = parentMatrix * m_localMatrix;
        m_worldPosition = parentMatrix * glm::vec4(m_localPosition, 1.0F);
        m_worldOrientation = m_parent->m_worldOrientation * m_localOrientation;
        m_worldScale = m_parent->m_worldScale * m_localScale;
    } else {
        m_worldMatrix = m_localMatrix;
        m_worldPosition = m_localPosition;
        m_worldOrientation = m_localOrientation;
        m_worldScale = m_localScale;
    }

    for (const auto child: m_children) {
        child->update();
    }
}

Entity::Entity(const bool isCamera) : m_isCamera(isCamera), m_isActive(true) {
    update();
}

Entity::~Entity() {
    for (const auto child : m_children) {
        child->setParent(nullptr);
    }
}

glm::vec3 Entity::worldToLocal(const glm::vec3 &vec) const {
    glm::vec3 result = m_worldPosition - vec;
    result = inverse(m_worldOrientation) * result;
    result /= m_worldScale;
    return result;
}

glm::vec3 Entity::localToWorld(const glm::vec3 &vec) const {
    return m_worldOrientation * (vec * m_worldScale) + m_worldPosition;
}

void Entity::setParent(Entity* parent) { // NOLINT(*-no-recursion)
    if (m_parent and m_parent != parent) {
        m_parent->removeChild(this);
    }

    const auto worldPosition = m_worldPosition;
    const auto worldOrientation = m_worldOrientation;
    const auto worldScale = m_worldScale;

    m_parent = parent;
    update();

    m_parent->addChild(this);
}

void Entity::addChild(Entity* child) { // NOLINT(*-no-recursion)
    if (std::ranges::find(m_children, child) != m_children.end()) return;
    m_children.push_back(child);
    child->setParent(this);
}

void Entity::removeChild(Entity *child) { // NOLINT(*-no-recursion)
    const auto childIt = std::ranges::find(m_children, child);
    if (childIt == m_children.end()) return;
    m_children.erase(childIt);
    child->setParent(nullptr);
}


