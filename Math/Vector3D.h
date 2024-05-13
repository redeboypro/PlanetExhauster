//
// Created by redeb on 13.05.2024.
//

#ifndef VECTOR3D_H
#define VECTOR3D_H
#include "Vector.h"

template<class T>
class Vector3D final : Vector<T, 3> {
public:
    Vector3D() = default;
    Vector3D(const T& x, const T& y, const T& z)  : x(x), y(y), z(z) {}
    Vector3D(const Vector3D& other) : x(other.x), y(other.y), z(other.z) {}

    explicit Vector3D(const T& scale) : x(scale), y(scale), z(scale) {}

    float& x = this->m_components[0];
    float& y = this->m_components[1];
    float& z = this->m_components[2];
};

#endif //VECTOR3D_H
