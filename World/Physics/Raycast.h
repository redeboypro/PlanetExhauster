//
// Created by redeb on 04.06.2024.
//

#ifndef RAYCAST_H
#define RAYCAST_H
#include <vec3.hpp>
#include <gtx/quaternion.hpp>
#include <cfloat>
#include <detail/func_geometric.inl>

#include "../../Mesh.h"

struct RaycastHit {
    glm::vec3 hitPoint;
    glm::vec3 hitNormal;
};

class Raycast final {
    static bool plane(
        const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
        const glm::vec3& planeOrigin, const glm::vec3& planeNormal,
        RaycastHit& raycastHit);

    static bool box(
        const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection,
        const glm::vec3& min, const glm::vec3& max,
        RaycastHit& raycastHit);

    static bool triangle(
        const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection,
        const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& normal,
        RaycastHit& raycastHit);

    static bool mesh(
        const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection,
        Mesh* mesh,
        const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale,
        RaycastHit& raycastHit);
};



#endif //RAYCAST_H
