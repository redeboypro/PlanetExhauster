//
// Created by redeb on 13.05.2024.
//

#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#include "Matrix.h"

template<class T>
class Matrix4x4 final : Matrix<T, 4, 4> {
public:
    Matrix4x4() = default;
    explicit Matrix4x4(Vector<T, 4>* rows) : Matrix<T, 4, 4>(rows) {}
};

#endif //MATRIX4X4_H
