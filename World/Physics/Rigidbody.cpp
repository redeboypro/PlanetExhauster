//
// Created by redeb on 25.05.2024.
//

#include "Rigidbody.h"

#include "EPA.h"
#include "GJK.h"

void Rigidbody::resolveCollision(
    Rigidbody *other,
    std::vector<Rigidbody*>& triggers,
    std::vector<Response>& responses) {
    for (const auto shapeA : m_collisionShapes) {
        if (!shapeA) continue;

        for (const auto shapeB : other->m_collisionShapes) {
            if (!shapeB) continue;

            EntityCollision collsionA = {other->m_entity, shapeB};
            EntityCollision collsionB = {m_entity, shapeA};

            if (Simplex simplex; GJK::gjk(collsionA, collsionB, simplex)) {
                if (other->isTrigger) {
                    triggers.push_back(other);
                } else {
                    auto collisionInfo = EPA::epa(simplex, collsionA, collsionB);
                    m_entity->setLocalPosition(m_entity->getLocalPosition() + collisionInfo.normal * collisionInfo.penetrationDepth);
                    if (collisionEnter) collisionEnter(other, collisionInfo);

                    if (collisionInfo.normal.y >= m_stepLimitAngle) {
                        m_fallVelocity = 0.0f;
                        m_isGrounded = true;
                    }

                    responses.push_back({other, collisionInfo});
                }
            }
        }
    }
}

void Rigidbody::refreshTriggers(const std::vector<Rigidbody*>& others) {
    for (auto elder : m_triggerContacts) {
        if (std::ranges::find(others, elder) == others.end()) {
            if (triggerExit) triggerExit(elder);
        }
    }

    for (auto newcomer : others){
        if (std::ranges::find(m_triggerContacts, newcomer) == m_triggerContacts.end()) {
            if (triggerEnter) triggerEnter(newcomer);
        }
    }

    m_triggerContacts = others;
}

void Rigidbody::refreshResponses(const std::vector<Response> &responses) {
    for (const auto [rigidbody, collision] : m_responses) {
        if (std::find_if(responses.begin(), responses.end(),
        [&](const std::pair<Rigidbody*, Collision> &localResponse) {
            return localResponse.first == rigidbody;
        }) == responses.end()) {
            if (collisionExit) collisionExit(rigidbody, collision);
        }
    }

    bool isGrounded = false;
    for (auto [rigidbody, collision] : responses){
        if (auto [normal, penetrationDepth] = collision; normal.y >= m_stepLimitAngle) {
            isGrounded = true;
        }
    }

    m_isGrounded = isGrounded;
    m_responses = responses;
}
