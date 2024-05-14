//
// Created by redeb on 13.05.2024.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <array>
#include <stdfloat>
#include <cstdint>

#define X 0
#define Y 1
#define Z 2
#define W 3

template<typename T, size_t SIZE>
struct Vector {
    friend struct MathDetail;

    using valueType = T;
    static constexpr size_t size = SIZE;

    Vector() = default;

    template<typename... ValueT>
    requires(sizeof...(ValueT) == SIZE && ((std::is_same_v<ValueT, T>) && ...))
    explicit Vector(const ValueT&... vals) noexcept {
        m_values = { vals... };
    }

    T& operator[](const size_t index) {
        return m_values[index];
    }

protected:
    std::array<T, SIZE> m_values { };
};

template<typename T>
struct Vector2Imp : Vector<T, 2> {
    T& x = this->m_values[X];
    T& y = this->m_values[Y];

    Vector2Imp() = default;

    template<typename... ValueT>
    requires(sizeof...(ValueT) == 2 && ((std::is_same_v<ValueT, T>) && ...))
    explicit Vector2Imp(const ValueT&... vals) noexcept {
        this->m_values = { vals... };
    }
};

template<typename T>
struct Vector3Imp : Vector<T, 3> {
    T& x = this->m_values[X];
    T& y = this->m_values[Y];
    T& z = this->m_values[Z];

    Vector3Imp() = default;

    template<typename... ValueT>
    requires(sizeof...(ValueT) == 3 && ((std::is_same_v<ValueT, T>) && ...))
    explicit Vector3Imp(const ValueT&... vals) noexcept {
        this->m_values = { vals... };
    }
};

template<typename T>
struct Vector4Imp : Vector<T, 4> {
    T& x = this->m_values[X];
    T& y = this->m_values[Y];
    T& z = this->m_values[Z];
    T& w = this->m_values[W];

    Vector4Imp() = default;

    template<typename... ValueT>
    requires(sizeof...(ValueT) == 4 && ((std::is_same_v<ValueT, T>) && ...))
    explicit Vector4Imp(const ValueT&... vals) noexcept {
        this->m_values = { vals... };
    }
};

using Vector2F16 = Vector2Imp<std::float16_t>;
using Vector3F16 = Vector3Imp<std::float16_t>;
using Vector4F16 = Vector4Imp<std::float16_t>;
using Vector2F32 = Vector2Imp<std::float32_t>;
using Vector3F32 = Vector3Imp<std::float32_t>;
using Vector4F32 = Vector4Imp<std::float32_t>;
using Vector2F64 = Vector2Imp<std::float64_t>;
using Vector3F64 = Vector3Imp<std::float64_t>;
using Vector4F64 = Vector4Imp<std::float64_t>;
using Vector2I16 = Vector2Imp<int16_t>;
using Vector3I16 = Vector3Imp<int16_t>;
using Vector4I16 = Vector4Imp<int16_t>;
using Vector2I32 = Vector2Imp<int32_t>;
using Vector3I32 = Vector3Imp<int32_t>;
using Vector4I32 = Vector4Imp<int32_t>;
using Vector2I64 = Vector2Imp<int64_t>;
using Vector3I64 = Vector3Imp<int64_t>;
using Vector4I64 = Vector4Imp<int64_t>;

#endif //VECTOR_H
