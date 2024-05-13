//
// Created by redeb on 13.05.2024.
//

#ifndef VECTOR_H
#define VECTOR_H


template<typename T, size_t SIZE>
class Vector {
protected:
    T m_components[SIZE];

public:
    T& operator[](const size_t& index) {
        return m_components[index];
    }
};


#endif //VECTOR_H
