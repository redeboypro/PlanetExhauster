//
// Created by redeb on 13.05.2024.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <array>

#include "Vector.h"

template<typename T, size_t ROWS, size_t COLUMNS>
struct Matrix
{
    friend struct MathDetail;

    using valueType = T;
    using vectorTemplate = Vector<T, COLUMNS>;

    static constexpr size_t numRows = ROWS;
    static constexpr size_t numColumns = COLUMNS;
    static constexpr size_t size = numRows * numColumns;

    Matrix() = default;

    template<typename... VectorT>
    requires(((VectorT::size == COLUMNS) && ...) && sizeof...(VectorT) == ROWS && ((std::is_same_v<typename VectorT::type, T>) && ...))
    explicit Matrix(const VectorT&... vecs) noexcept {
        m_values = { vecs... };
    }

    Vector<T, COLUMNS>& operator[](const size_t index) {
        return m_values[index];
    }

protected:
    std::array<Vector<T, COLUMNS>, ROWS> m_values {};
};

template<typename T>
struct Matrix4Imp : Matrix<T, 4, 4> {
    Vector4Imp<T>& row0 = this->m_colums[X];
    Vector4Imp<T>& row1 = this->m_colums[Y];
    Vector4Imp<T>& row2 = this->m_colums[Z];
    Vector4Imp<T>& row3 = this->m_colums[W];

    T& m00 = this[0][0]; T& m01 = this[1][0]; T& m02 = this[2][0]; T& m03 = this[3][0];
    T& m10 = this[0][1]; T& m11 = this[1][1]; T& m12 = this[2][1]; T& m13 = this[3][1];
    T& m20 = this[0][2]; T& m21 = this[1][2]; T& m22 = this[2][2]; T& m23 = this[3][2];
    T& m30 = this[0][3]; T& m31 = this[1][3]; T& m32 = this[2][3]; T& m33 = this[3][3];
};

using Matrix4F16 = Matrix4Imp<std::float16_t>;
using Matrix4F32 = Matrix4Imp<std::float32_t>;
using Matrix4F64 = Matrix4Imp<std::float64_t>;
using Matrix4I16 = Matrix4Imp<int16_t>;
using Matrix4I32 = Matrix4Imp<int32_t>;
using Matrix4I64 = Matrix4Imp<int64_t>;

#endif //MATRIX_H
