//
// Created by redeb on 04.06.2024.
//

#include "Raycast.h"

bool Raycast::plane(
    const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection,
    const glm::vec3 &planeOrigin, const glm::vec3 &planeNormal,
    RaycastHit &raycastHit) {
    const float planeDotRay = dot(planeNormal, rayDirection);
    raycastHit.hitPoint = rayOrigin + rayDirection;
    raycastHit.hitNormal = {};

    if (std::abs(planeDotRay) <= FLT_EPSILON) {
        return false;
    }

    const auto distanceToHitPoint = dot(planeOrigin - rayOrigin, planeNormal) / planeDotRay;
    raycastHit.hitPoint = rayOrigin + rayDirection * distanceToHitPoint;
    raycastHit.hitNormal = planeNormal;

    return distanceToHitPoint >= 0;
}

bool Raycast::box(
    const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection,
    const glm::vec3 &min, const glm::vec3 &max,
    RaycastHit &raycastHit) {
    raycastHit.hitPoint = rayOrigin + rayDirection;
    raycastHit.hitNormal = {};

    glm::vec3 fracDirection;
    fracDirection.x = 1.0F / rayDirection.x;
    fracDirection.y = 1.0F / rayDirection.y;
    fracDirection.z = 1.0F / rayDirection.z;

    const float distanceToMinX = (min.x - rayOrigin.x) * fracDirection.x;
    const float distanceToMaxX = (max.x - rayOrigin.x) * fracDirection.x;

    const float distanceToMinY = (min.y - rayOrigin.y) * fracDirection.y;
    const float distanceToMaxY = (max.y - rayOrigin.y) * fracDirection.y;

    const float distanceToMinZ = (min.z - rayOrigin.z) * fracDirection.z;
    const float distanceToMaxZ = (max.z - rayOrigin.z) * fracDirection.z;

    const float distanceToMin = std::max(std::max(
        std::min(distanceToMinX, distanceToMaxX),
        std::min(distanceToMinY, distanceToMaxY)),
        std::min(distanceToMinZ, distanceToMaxZ));

    const float distanceToMax = std::min(std::min(
        std::max(distanceToMinX, distanceToMaxX),
        std::max(distanceToMinY, distanceToMaxY)),
        std::max(distanceToMinZ, distanceToMaxZ));

    if (distanceToMax < 0) {
        return false;
    }

    if (distanceToMin > distanceToMax) {
        return false;
    }

    raycastHit.hitPoint = rayOrigin + rayDirection * distanceToMin;

    // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
    switch (distanceToMin) {
        case distanceToMinX : {
            raycastHit.hitNormal = {-1, 0, 0};
        }
        case distanceToMaxX : {
            raycastHit.hitNormal = {1, 0, 0};
        }
        case distanceToMinY : {
            raycastHit.hitNormal = {0, -1, 0};
        }
        case distanceToMaxY : {
            raycastHit.hitNormal = {0, 1, 0};
        }
        case distanceToMinZ : {
            raycastHit.hitNormal = {0, 0, -1};
        }
        case distanceToMaxZ : {
            raycastHit.hitNormal = {0, 0, 1};
        }
    }

    return true;
}

bool Raycast::triangle(
    const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection,
    const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, const glm::vec3 &normal,
    RaycastHit &raycastHit) {
    const float normalDotRay = dot(normal, rayDirection);
    raycastHit.hitPoint = rayOrigin + rayDirection;
    raycastHit.hitNormal = {};

    if (abs(normalDotRay) < FLT_EPSILON) {
        return false;
    }

    const float normalDotPoint = -dot(normal, a);
    const float distanceToHitPoint = -(dot(normal, rayOrigin) + normalDotPoint) / normalDotRay;

    if (distanceToHitPoint < 0) {
        return false;
    }

    raycastHit.hitPoint = rayOrigin + distanceToHitPoint * rayDirection;

    const auto triangleEdge1 = b - a;
    const auto rayTriangleDelta1 = raycastHit.hitPoint - a;
    auto crossProduct = cross(triangleEdge1, rayTriangleDelta1);
    if (dot(normal, crossProduct) < 0) {
        return false;
    }

    const auto triangleEdge2 = c - b;
    const auto rayTriangleDelta2 = raycastHit.hitPoint - b;
    crossProduct = cross(triangleEdge2, rayTriangleDelta2);
    if (dot(normal, crossProduct) < 0) {
        return false;
    }

    const auto triangleEdge3 = a - c;
    const auto rayTriangleDelta3 = raycastHit.hitPoint - c;
    crossProduct = cross(triangleEdge3, rayTriangleDelta3);

    raycastHit.hitNormal = normal;

    return dot(normal, crossProduct) >= 0;
}

bool Raycast::mesh(
    const glm::vec3 &rayOrigin, const glm::vec3 &rayDirection,
    Mesh *mesh,
    const glm::vec3 &position, const glm::quat &rotation, const glm::vec3 &scale,
    RaycastHit &raycastHit) {
    raycastHit.hitPoint = rayOrigin + rayDirection;

    uint32_t face[3];
    int32_t vertexId = 0;

    bool hitAny = false;
    float closestDistance = FLT_MAX;

    for (const auto index : mesh->indices) {
        face[vertexId++] = index;
        if (vertexId < 3) {
            continue;
        }

        const auto ai = face[0] * 3;
        glm::vec3 av;
        av.x = mesh->vertices[ai];
        av.y = mesh->vertices[ai + 1];
        av.z = mesh->vertices[ai + 2];
        av = rotation * (av * scale) + position;

        const auto bi = face[1] * 3;
        glm::vec3 bv;
        bv.x = mesh->vertices[bi];
        bv.y = mesh->vertices[bi + 1];
        bv.z = mesh->vertices[bi + 2];
        bv = rotation * (bv * scale) + position;

        const auto ci = face[2] * 3;
        glm::vec3 cv;
        cv.x = mesh->vertices[ci];
        cv.y = mesh->vertices[ci + 1];
        cv.z = mesh->vertices[ci + 2];
        cv = rotation * (cv * scale) + position;
        auto normal = cross(bv - av, cv - av);

        if (RaycastHit triangleHit {}; triangle(rayOrigin, rayDirection, av, bv, cv,
            normal, triangleHit)) {
            hitAny = true;
            if (float distance = glm::distance(triangleHit.hitPoint, raycastHit.hitPoint);
                distance < closestDistance) {
                raycastHit.hitPoint = triangleHit.hitPoint;
                closestDistance = distance;
            }
        }

        vertexId = 0;
    }

    return hitAny;
}
