//
// Created by redeb on 31.05.2024.
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include <GL/gl.h>

constexpr static GLfloat quad_vertices[8] {
    -0.5, 0.5,
    -0.5, -0.5,
    0.5, 0.5,
    0.5, -0.5
};

constexpr static GLfloat quad_uv[8] = {
    0, 0,
    0, 1,
    1, 0,
    1, 1
};

#endif //PRIMITIVES_H
