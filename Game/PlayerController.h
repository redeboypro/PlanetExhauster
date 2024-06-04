//
// Created by redeb on 01.06.2024.
//

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "../World/World.h"
#include "../Input.h"

#define PLAYER_SIZE         0.5F
#define PLAYER_SPEED        3.0F
#define CAMERA_SPEED        10.0F
#define CAMERA_PITCH_MIN    (-90.0F)
#define CAMERA_PITCH_MAX    90.0F
#define PLAYER_JUMP_FORCE   5.0F

#define CLAMP(ANGLE, MIN, MAX) ANGLE < MIN ? MIN : ANGLE > MAX ? MAX : ANGLE

class PlayerController final {
    Rigidbody* m_player;
    Entity* m_playerEnt;
    Entity* m_cameraEnt;
    Input* m_input;
    Collider* m_collider;

    GLfloat m_pitch, m_yaw;

    void move(const glm::vec3& vec) const;

public:
    PlayerController(World* world, Input* input);
    ~PlayerController();

    [[nodiscard]] Rigidbody* getRigidbody() const;

    void update(GLfloat deltaTime);
};



#endif //PLAYERCONTROLLER_H
