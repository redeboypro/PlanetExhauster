//
// Created by redeb on 13.05.2024.
//

#ifndef MATRIX_H
#define MATRIX_H
#include "Vector.h"

template<typename T, size_t COLUMNS, size_t ROWS>
class Matrix {
protected:
    Vector<T, COLUMNS> m_rows[ROWS];

public:
    Vector<T, COLUMNS>& operator[](const size_t row) {
        return m_rows[row];
    }
};

#endif //MATRIX_H
