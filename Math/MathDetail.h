//
// Created by redeb on 14.05.2024.
//

#ifndef MATHDETAIL_H
#define MATHDETAIL_H



class MathDetail {
    template<typename T>
    constexpr static auto* valuePtr(T& obj) {
        return reinterpret_cast<typename T::type*>(obj.values.data());
    }
};



#endif //MATHDETAIL_H
