//
// Created by redeb on 25.05.2024.
//

#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <functional>

#include "Collider.h"
#include "Collision.h"
#include "../Entity.h"

class Rigidbody;

typedef std::function<void(Rigidbody* rigidbody, Collision collision)> CollisionCallback;
typedef std::function<void(Rigidbody* rigidbody)> TriggerCallback;

struct Response final {
    Rigidbody* rigidbody;
    Collision collision;
};

class Rigidbody final {
    Entity* m_entity;
    std::vector<Response> m_responses;
    std::vector<Rigidbody*> m_triggerContacts;
    std::vector<Collider*> m_collisionShapes;
    std::vector<std::string> m_ignoreCollisionTags;
    bool m_isGrounded;
    float m_stepLimitAngle;
    float m_fallVelocity;
    float m_fallAcceleration;

public:
    explicit Rigidbody(const bool isCamera) :
    Rigidbody(new Entity(isCamera)) {}

    explicit Rigidbody(Entity* entity):
    m_entity(entity),
    m_isGrounded(false),
    m_stepLimitAngle(30.0F),
    m_fallVelocity(0),
    m_fallAcceleration(-80.0F),
    isKinematic(true),
    isTrigger(false) {}

    ~Rigidbody() {
        delete m_entity;
    }

    [[nodiscard]] Entity* getEntity() const {
        return m_entity;
    }

    const std::vector<Response>& getResponses() {
        return m_responses;
    }

    [[nodiscard]] float getStepLimitAngle() const {
        return m_stepLimitAngle;
    }

    void setStepLimitAngle(const float angle) {
        m_stepLimitAngle = angle / 90.0F;
    }

    [[nodiscard]] float getFallVelocity() const {
        return m_fallVelocity;
    }

    [[nodiscard]] float getFallAcceleration() const {
        return m_fallAcceleration;
    }

    void setFallAcceleration(const float angle) {
        m_fallAcceleration = angle;
    }

    void tossUp(const float force) {
        m_fallVelocity = force;
    }

    bool ignoresTag(const std::string& tag) {
        return std::ranges::find(m_ignoreCollisionTags, tag) != m_ignoreCollisionTags.end();
    }

    void setIgnoreTags(const std::initializer_list<std::string> tags) {
        m_ignoreCollisionTags = tags;
    }

    void setCollisionShapes(const std::initializer_list<Collider*> collisionShapes) {
        m_collisionShapes = collisionShapes;
    }

    void accelerateFall(const float deltaTime) {
        m_fallVelocity += m_fallAcceleration * deltaTime;
    }

    void resolveCollision(
        Rigidbody* other,
        std::vector<Rigidbody*>& triggers,
        std::vector<Response>& responses);

    void refreshTriggers(const std::vector<Rigidbody*>& others);
    void refreshResponses(const std::vector<Response>& responses);

    bool isKinematic, isTrigger;

    CollisionCallback collisionEnter = nullptr;
    CollisionCallback collisionExit = nullptr;

    TriggerCallback triggerEnter = nullptr;
    TriggerCallback triggerExit = nullptr;
};



#endif //RIGIDBODY_H
