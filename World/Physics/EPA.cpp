//
// Created by redeb on 25.05.2024.
//

#include "EPA.h"
#include "GJK.h"

namespace EPA {
    using namespace GJK;
    Collision epa(const Simplex &simplex, const EntityCollision& objA, const EntityCollision& objB) {
        std::vector polytope(simplex.begin(), simplex.end());
        std::vector<size_t> faces = {
            0, 1, 2,
            0, 3, 1,
            0, 2, 3,
            1, 3, 2
        };

        int32_t minTriangle;
        auto normals = getFaceNormals(polytope, faces, minTriangle);

        glm::vec3 minDirection = normals[minTriangle].direction;
        float minDistance = FLT_MAX;

        size_t iterationCount = 0;
        while (std::abs(minDistance - FLT_MAX) < std::numeric_limits<float>::epsilon() &&
            iterationCount++ < objA.collider->size() + objB.collider->size()) {
            if (minTriangle < 0 or minTriangle >= normals.size()) continue;

            const auto [direction, distance] = normals[minTriangle];
            minDirection = direction;
            minDistance = distance;

            glm::vec3 support = supportPoint(objA, objB, minDirection);

            if (const float sDistance = dot(minDirection, support); std::abs(sDistance - minDistance) > EPS) {
                minDistance = FLT_MAX;
                std::vector<std::pair<size_t, size_t>> uniqueEdges;

                long face = 0;
                for (const auto& [direction, distance]: normals) {
                    if (sameDirection(direction, support)) {
                        addIfUniqueEdge(uniqueEdges, faces, face, face + 1);
                        addIfUniqueEdge(uniqueEdges, faces, face + 1, face + 2);
                        addIfUniqueEdge(uniqueEdges, faces, face + 2, face);

                        faces.erase(faces.begin() + face);
                        faces.erase(faces.begin() + face);
                        faces.erase(faces.begin() + face);
                    }
                    else{
                        face += 3;
                    }
                }

                std::vector<size_t> newFaces;
                for (auto [edgeA, edgeB]: uniqueEdges) {
                    newFaces.push_back(edgeA);
                    newFaces.push_back(edgeB);
                    newFaces.push_back(polytope.size());
                }
                polytope.push_back(support);
                faces.insert(faces.end(), newFaces.begin(), newFaces.end());

                normals = getFaceNormals(polytope, faces, minTriangle);
            }
        }

        return std::abs(minDistance - FLT_MAX) < std::numeric_limits<float>::epsilon() ?
            Collision {minDirection, 0} :
        Collision {minDirection, minDistance + EPS};
    }

    std::vector<CollisionNormal> getFaceNormals(
        const std::vector<glm::vec3> &polytope,
        const std::vector<size_t> &faces,
        int32_t& minTriangle) {
        std::vector<CollisionNormal> normals;
        minTriangle = 0;
        float minDistance = FLT_MAX;

        for (int32_t i = 0; i < faces.size(); i += 3) {
            glm::vec3 a = polytope[faces[i]];
            glm::vec3 b = polytope[faces[i + 1]];
            glm::vec3 c = polytope[faces[i + 2]];

            glm::vec3 direction = normalize(cross(b - a, c - a));
            float distance = dot(direction, a);

            if (distance < 0) {
                direction = -direction;
                distance = -distance;
            }

            normals.push_back(CollisionNormal{direction, distance});

            if (distance < minDistance) {
                minTriangle = i / 3;
                minDistance = distance;
            }
        }

        return normals;
    }

    void addIfUniqueEdge(
        std::vector<std::pair<size_t, size_t>> &edges,
        const std::vector<size_t> &faces,
        const size_t a,
        const size_t b) {
        if (const auto reverse = std::ranges::find(edges,
        std::make_pair(faces[b], faces[a])); reverse != edges.end()) {
            edges.erase(reverse);
        } else {
            edges.emplace_back(faces[a], faces[b]);
        }
    }
}
