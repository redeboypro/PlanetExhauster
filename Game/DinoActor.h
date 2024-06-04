//
// Created by redeb on 03.06.2024.
//

#ifndef DINOACTOR_H
#define DINOACTOR_H

#include "../World/World.h"

#define DINO_JUMP_FORCE     4.0F
#define DINO_SPEED          2.0F
#define DINO_ROTATION_SPEED 2.0F

class DinoActor final {
    Rigidbody* m_dino;
    Entity* m_dinoEnt;
    Collider* m_collider = nullptr;

    Rigidbody* m_target = nullptr;
    Entity* m_targetEnt = nullptr;

    GLfloat m_angle;
public:
    explicit DinoActor(World* world);
    ~DinoActor();

    [[nodiscard]] Entity* getEntity() const;

    void setModelData(Mesh* mesh, TextureRgba* texture);
    void setTarget(Rigidbody* target);
    void update(GLfloat deltaTime) const;
};



#endif //DINOACTOR_H
