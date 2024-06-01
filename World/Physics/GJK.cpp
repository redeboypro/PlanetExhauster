//
// Created by redeb on 25.05.2024.
//

#include "GJK.h"

#include <iostream>

namespace GJK {
    glm::vec3 supportPoint(const EntityCollision& objA, const EntityCollision& objB, const glm::vec3 &direction) {
        return objA.collider->findFurthestPoint(objA.entity, direction) - objB.collider->findFurthestPoint(objB.entity, -direction);
    }

    bool gjk(const EntityCollision& objA, const EntityCollision& objB, Simplex& simplex) {
        glm::vec3 support = supportPoint(objA, objB, glm::vec3(1, 0, 0));
        glm::vec3 direction = -support;

        simplex.push(support);

        int32_t iterations = 0;
        while (iterations++ < objA.collider->size() + objB.collider->size()) {
            support = supportPoint(objA, objB, direction);

            if (dot(support, direction) <= 0) {
                return false;
            }

            simplex.push(support);
            if (nextSimplex(simplex, direction)) {
                return true;
            }
        }

        return false;
    }

    bool nextSimplex(Simplex& simplex, glm::vec3& direction) {
        switch (simplex.size()) {
            case 2: return line(simplex, direction);
            case 3: return triangle(simplex, direction);
            case 4: return tetrahedron(simplex, direction);
            default: return false;
        }
    }

    bool sameDirection(const glm::vec3& direction, const glm::vec3& ao) {
        return dot(direction, ao) > 0;
    }

    bool line(Simplex& simplex, glm::vec3& direction) {
        glm::vec3 a = simplex[0];
        const glm::vec3 b = simplex[1];
        const glm::vec3 ab = b - a;

        if (const glm::vec3 ao = -a; sameDirection(ab, ao)) {
            direction = cross(cross(ab, ao), ab);
        } else {
            simplex = { a };
            direction = ao;
        }

        return false;
    }

    // ReSharper disable once CppDFAConstantFunctionResult
    bool triangle(Simplex& simplex, glm::vec3& direction) {
        glm::vec3 a = simplex[0];
        glm::vec3 b = simplex[1];
        glm::vec3 c = simplex[2];

        const glm::vec3 ab = b - a;
        const glm::vec3 ac = c - a;
        const glm::vec3 ao = -a;

        if (const glm::vec3 abc = cross(ab, ac); sameDirection(cross(abc, ac), ao)) {
            if (sameDirection(ac, ao)) {
                simplex = { a, c };
                direction = cross(cross(ac, ao), ac);
            } else {
                return line(simplex = { a, b }, direction);
            }
        } else {
            if (sameDirection(cross(ab, abc), ao)) {
                return line(simplex = { a, b }, direction);
            }

            if (sameDirection(abc, ao)) {
                direction = abc;
            } else {
                simplex = { a, c, b };
                direction = -abc;
            }
        }

        return false;
    }

    bool tetrahedron(Simplex &simplex, glm::vec3 &direction) {
        glm::vec3 a = simplex[0];
        glm::vec3 b = simplex[1];
        glm::vec3 c = simplex[2];
        glm::vec3 d = simplex[3];

        glm::vec3 ab = b - a;
        glm::vec3 ac = c - a;
        glm::vec3 ad = d - a;
        glm::vec3 ao = -a;

        glm::vec3 abc = cross(ab, ac);
        glm::vec3 acd = cross(ac, ad);
        glm::vec3 adb = cross(ad, ab);

        if (sameDirection(abc, ao)) {
            return triangle(simplex = { a, b, c }, direction);
        }

        if (sameDirection(acd, ao)) {
            return triangle(simplex = { a, c, d }, direction);
        }

        if (sameDirection(adb, ao)) {
            return triangle(simplex = { a, d, b }, direction);
        }

        return true;
    }
}
