//
// Created by 邱姜铭 on 2023/10/19.
//

#ifndef ABSTRACTVECTOR_MYMATHVECTOR_H
#define ABSTRACTVECTOR_MYMATHVECTOR_H

#include <iostream>
#include <type_traits>
#include "MyVector.h"
#include "MyString.h"

template<typename T>
class MyMathVector : public MyVector<T> {
public:

    typedef T value_type;

    typedef typename MyVector<T>::size_type size_type;

    MyMathVector() = default;

    MyMathVector(const value_type *data, size_type size);

    MyMathVector(value_type *&&data, size_type size);

    MyMathVector(const MyMathVector &v);

    MyMathVector(MyMathVector &&v) noexcept;

    MyMathVector &operator=(const MyMathVector &v);

    MyMathVector &operator=(MyMathVector &&v) noexcept;

    bool operator==(const MyMathVector &v) const;

    bool operator!=(const MyMathVector &v) const;

    MyMathVector operator+() const;

    MyMathVector operator+(const MyMathVector &v) const;

    MyMathVector operator-() const;

    MyMathVector operator-(const MyMathVector &v) const;

    MyMathVector operator*(value_type k) const;

    MyMathVector &operator+=(const MyMathVector &v);

    MyMathVector &operator-=(const MyMathVector &v);

    MyMathVector &operator*=(value_type k);

    std::ostream &operator<<(std::ostream &os) const;

    friend std::ostream &operator<<(std::ostream &os, MyMathVector const &vector) {
        vector.operator<<(os);
        return os;
    }

    std::istream &operator>>(std::istream &is);

    friend std::istream &operator>>(std::istream &is, MyMathVector &vector) {
        vector.operator>>(is);
        return is;
    }

    // 点乘
    [[nodiscard]] value_type dot(const MyMathVector &v) const;

    // 叉乘
    [[nodiscard]] MyMathVector cross(const MyMathVector &v) const;

    [[nodiscard]] const char *toString() const override;


private:
    // 精度
    const double EPS = 1e-6;

    bool isZero(value_type x) const {
        if (std::is_same<T, float>::value || std::is_same<T, double>::value) {
            return fabs(x) < EPS;
        }
        return x == 0;
    }

    void checkSize(const MyMathVector &v) const {
        if (this->size != v.size) {
            throw std::invalid_argument("Vectors must have the same size");
        }
    }

};

template<typename T>
MyMathVector<T>::MyMathVector(const value_type *data, size_type size) : MyVector<T>(data, size) {}

template<typename T>
MyMathVector<T>::MyMathVector(value_type *&&data, size_type size) : MyVector<T>(data, size) {}

template<typename T>
MyMathVector<T>::MyMathVector(const MyMathVector &v) : MyVector<T>(v) {}

template<typename T>
MyMathVector<T>::MyMathVector(MyMathVector &&v) noexcept: MyVector<T>(std::move(v)) {}

template<typename T>
MyMathVector<T> &MyMathVector<T>::operator=(const MyMathVector &v) {
    MyVector<T>::operator=(v);
    return *this;
}

template<typename T>
MyMathVector<T> &MyMathVector<T>::operator=(MyMathVector &&v) noexcept {
    MyVector<T>::operator=(std::move(v));
    return *this;
}

template<typename T>
bool MyMathVector<T>::operator==(const MyMathVector &v) const {
    for (int i = 0; i < this->size; ++i) {
        if (!isZero(this->data[i] - v.data[i])) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool MyMathVector<T>::operator!=(const MyMathVector &v) const {
    return !operator==(v);
}

template<typename T>
MyMathVector<T> MyMathVector<T>::operator+(const MyMathVector &v) const {
    checkSize(v);
    MyMathVector result;
    result.resize(this->size);
    for (int i = 0; i < this->size; ++i) {
        result[i] = this->data[i] + v.data[i];
    }
    return result;
}

template<typename T>
MyMathVector<T> MyMathVector<T>::operator-(const MyMathVector &v) const {
    checkSize(v);
    MyMathVector result;
    result.resize(this->size);
    for (int i = 0; i < this->size; ++i) {
        result[i] = this->data[i] - v.data[i];
    }
    return result;
}

template<typename T>
MyMathVector<T> MyMathVector<T>::operator*(value_type k) const {
    MyMathVector result;
    result.resize(this->size);
    for (int i = 0; i < this->size; ++i) {
        result[i] = this->data[i] * k;
    }
    return result;
}

template<typename T>
MyMathVector<T> &MyMathVector<T>::operator+=(const MyMathVector &v) {
    checkSize(v);
    for (int i = 0; i < this->size; ++i) {
        this->data[i] += v.data[i];
    }
    return *this;
}

template<typename T>
MyMathVector<T> &MyMathVector<T>::operator-=(const MyMathVector &v) {
    checkSize(v);
    for (int i = 0; i < this->size; ++i) {
        this->data[i] -= v.data[i];
    }
    return *this;
}

template<typename T>
MyMathVector<T> &MyMathVector<T>::operator*=(value_type k) {
    for (int i = 0; i < this->size; ++i) {
        this->data[i] *= k;
    }
    return *this;
}

template<typename T>
MyMathVector<T> MyMathVector<T>::operator+() const {
    return *this;
}

template<typename T>
MyMathVector<T> MyMathVector<T>::operator-() const {
    MyMathVector result;
    result.resize(this->size);
    for (int i = 0; i < this->size; ++i) {
        result[i] = -this->data[i];
    }
    return result;
}

template<typename T>
std::ostream &MyMathVector<T>::operator<<(std::ostream &os) const {
    os << toString();
    return os;
}

template<typename T>
std::istream &MyMathVector<T>::operator>>(std::istream &is) {
    for (int i = 0; i < this->size; ++i) {
        is >> (this->data[i]);
    }
    return is;
}

template<typename T>
typename MyMathVector<T>::value_type MyMathVector<T>::dot(const MyMathVector &v) const {
    checkSize(v);
    value_type result = 0;
    for (int i = 0; i < v.size; ++i) {
        result += this->data[i] * v.data[i];
    }
    return result;
}

template<typename T>
MyMathVector<T> MyMathVector<T>::cross(const MyMathVector &v) const {
    if (this->size != 3 || v.size != 3) {
        throw std::invalid_argument("Cross product is only defined for 3D vectors");
    }
    MyMathVector result;
    result.resize(3);
    result[0] = this->data[1] * v.data[2] - this->data[2] * v.data[1];
    result[1] = this->data[2] * v.data[0] - this->data[0] * v.data[2];
    result[2] = this->data[0] * v.data[1] - this->data[1] * v.data[0];
    return result;
}

template<typename T>
const char *MyMathVector<T>::toString() const {
    MyString result;
    result.push_back('(');
    for (int i = 0; i < this->size; ++i) {
        if (std::is_same<T, char>::value) {
            result.push_back(this->data[i]);
        } else {
            result += MyString(std::to_string(this->data[i]));
        }
        if (i != this->size - 1) {
            result.push_back(',');
            result.push_back(' ');
        }
    }
    result.push_back(')');
    return result.toString();
}


#endif //ABSTRACTVECTOR_MYMATHVECTOR_H
