//
// Created by redeb on 25.05.2024.
//

#include "GJK.h"

#include "Simplex.h"

namespace GJK {
    glm::vec3 GJK::supportPoint(const Collider &colliderA, const Collider &colliderB, const glm::vec3 &direction) {
        return colliderA.findFurthestPoint( direction) - colliderB.findFurthestPoint(-direction);
    }

    bool GJK::gjk(const Collider &colliderA, const Collider &colliderB) {
        glm::vec3 support = supportPoint(colliderA, colliderB, glm::vec3(1, 0, 0));

        Simplex points;
        points.push(support);

        glm::vec3 direction = -support;
        while (true) {
            support = supportPoint(colliderA, colliderB, direction);

            if (dot(support, direction) <= 0) {
                return false;
            }

            points.push(support);
            if (nextSimplex(points, direction)) {
                return true;
            }
        }
    }

    bool GJK::nextSimplex(Simplex &simplex, glm::vec3 &direction) {
        switch (simplex.size()) {
            case 2: return line(simplex, direction);
            case 3: return triangle(simplex, direction);
            case 4: return tetrahedron(simplex, direction);
        }

        return false;
    }

    bool GJK::sameDirection(const glm::vec3 &direction, const glm::vec3 &ao) {
        return dot(direction, ao) > 0;
    }

    bool GJK::line(Simplex &simplex, glm::vec3 &direction) {
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
    bool GJK::triangle(Simplex &simplex, glm::vec3 &direction) {
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
        }

        else {
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

    bool GJK::tetrahedron(Simplex &simplex, glm::vec3 &direction) {
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
