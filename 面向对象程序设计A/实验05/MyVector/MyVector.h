//
// Created by 邱姜铭 on 2023/9/28.
//

#ifndef MYVECTOR_MYVECTOR_H
#define MYVECTOR_MYVECTOR_H

#include <iostream>

template<class T>
class MyVector {
public:

    typedef T value_type;

    typedef int size_type;

    MyVector();

    MyVector(size_type dim, value_type *&&data);

    MyVector(size_type dim, const value_type *data);

    MyVector(const MyVector &v);

    MyVector(MyVector &&v) noexcept;

    ~MyVector();

    void resize(size_type new_dim);

    std::ostream &operator<<(std::ostream &os) const;

    friend std::ostream &operator<<(std::ostream &os, const MyVector<T> &v) {
        return v.operator<<(os);
    }

    std::istream &operator>>(std::istream &is);

    friend std::istream &operator>>(std::istream &is, MyVector<T> &v) {
        return v.operator>>(is);
    }

    bool operator==(const MyVector &v) const;

    bool operator!=(const MyVector &v) const;

    MyVector &operator=(const MyVector &v);

    MyVector &operator=(MyVector &&v) noexcept;

    MyVector operator+(const MyVector &v) const;

    MyVector &operator+=(const MyVector &v);

    MyVector operator-(const MyVector &v) const;

    MyVector operator-() const;

    MyVector &operator-=(const MyVector &v);

    value_type operator*(const MyVector &v) const;

    MyVector operator*(value_type k) const;

    MyVector &operator*=(value_type k);

    MyVector cross(const MyVector &v) const;

    value_type &operator[](size_type i);

    const value_type &operator[](size_type i) const;

    size_type getDim() const;

private:
    void checkDim(const MyVector &v) const noexcept(false);

    value_type *data;
    size_type dim;
};

template<class T>
MyVector<T>::MyVector() {
    this->dim = 0;
    this->data = new value_type[0]{};
}

template<class T>
MyVector<T>::MyVector(size_type dim, value_type *&&data) {
    if (dim < 0) {
        throw std::invalid_argument("Dimension must be non-negative");
    }
    this->dim = dim;
    this->data = data;
}

template<class T>
MyVector<T>::MyVector(size_type dim, const value_type *data) {
    if (dim < 0) {
        throw std::invalid_argument("Dimension must be non-negative");
    }
    this->dim = dim;
    this->data = new value_type[dim];
    for (size_type i = 0; i < dim; ++i) {
        this->data[i] = data[i];
    }
}

template<class T>
MyVector<T>::MyVector(const MyVector &v) {
    this->dim = v.dim;
    this->data = new value_type[dim];
    for (size_type i = 0; i < dim; ++i) {
        this->data[i] = v.data[i];
    }
}

template<class T>
MyVector<T>::MyVector(MyVector &&v) noexcept {
    this->dim = v.dim;
    this->data = v.data;
    v.data = nullptr;
    v.dim = 0;
}

template<class T>
MyVector<T>::~MyVector() {
    delete[] data;
}

template<class T>
void MyVector<T>::resize(size_type new_dim) {
    if (new_dim < 0) {
        throw std::invalid_argument("Dimension must be non-negative");
    }
    value_type *new_data = new value_type[new_dim];
    for (size_type i = 0; i < new_dim; ++i) {
        new_data[i] = i < dim ? data[i] : 0;
    }
    delete[] data;
    this->data = new_data;
    this->dim = new_dim;
}

template<class T>
std::ostream &MyVector<T>::operator<<(std::ostream &os) const {
    os << "(";
    for (size_type i = 0; i < dim; ++i) {
        os << data[i];
        if (i != dim - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}

template<class T>
std::istream &MyVector<T>::operator>>(std::istream &is) {
    for (size_type i = 0; i < dim; ++i) {
        is >> data[i];
    }
    return is;
}

template<class T>
bool MyVector<T>::operator==(const MyVector &v) const {
    if (dim != v.dim) {
        return false;
    }
    for (size_type i = 0; i < dim; ++i) {
        if (data[i] != v.data[i]) {
            return false;
        }
    }
    return true;
}

template<class T>
bool MyVector<T>::operator!=(const MyVector &v) const {
    return !operator==(v);
}

template<class T>
MyVector<T> &MyVector<T>::operator=(const MyVector &v) {
    if (this == &v) {
        return *this;
    }
    delete[] data;
    this->dim = v.dim;
    this->data = new value_type[dim];
    for (size_type i = 0; i < dim; ++i) {
        this->data[i] = v.data[i];
    }
    return *this;
}

template<class T>
MyVector<T> &MyVector<T>::operator=(MyVector<T> &&v) noexcept {
    if (this == &v) {
        return *this;
    }
    this->dim = v.dim;
    this->data = v.data;
    v.dim = 0;
    v.data = nullptr;
    return *this;
}

template<class T>
MyVector<T> MyVector<T>::operator+(const MyVector &v) const {
    checkDim(v);
    MyVector result(*this);
    for (size_type i = 0; i < dim; ++i) {
        result.data[i] += v.data[i];
    }
    return result;
}

template<class T>
MyVector<T> &MyVector<T>::operator+=(const MyVector &v) {
    checkDim(v);
    for (size_type i = 0; i < dim; ++i) {
        data[i] += v.data[i];
    }
    return *this;
}

template<class T>
MyVector<T> MyVector<T>::operator-(const MyVector &v) const {
    checkDim(v);
    MyVector result(*this);
    for (size_type i = 0; i < dim; ++i) {
        result.data[i] -= v.data[i];
    }
    return result;
}

template<class T>
MyVector<T> MyVector<T>::operator-() const {
    MyVector result(*this);
    for (size_type i = 0; i < dim; ++i) {
        result.data[i] = -result.data[i];
    }
    return result;
}

template<class T>
MyVector<T> &MyVector<T>::operator-=(const MyVector &v) {
    checkDim(v);
    for (size_type i = 0; i < dim; ++i) {
        data[i] -= v.data[i];
    }
    return *this;
}

template<class T>
typename MyVector<T>::value_type MyVector<T>::operator*(const MyVector &v) const {
    checkDim(v);
    value_type result = 0;
    for (size_type i = 0; i < dim; ++i) {
        result += data[i] * v.data[i];
    }
    return result;
}

template<class T>
MyVector<T> MyVector<T>::operator*(value_type k) const {
    MyVector result(*this);
    for (size_type i = 0; i < dim; ++i) {
        result.data[i] *= k;
    }
    return result;
}

template<class T>
MyVector<T> &MyVector<T>::operator*=(value_type k) {
    for (size_type i = 0; i < dim; ++i) {
        data[i] *= k;
    }
    return *this;
}

template<class T>
MyVector<T> MyVector<T>::cross(const MyVector &v) const {
    if (dim != 3 || v.dim != 3) {
        throw std::invalid_argument("Dimension mismatch");
    }
    MyVector result(3, new value_type[3]{data[1] * v.data[2] - data[2] * v.data[1],
                                         data[2] * v.data[0] - data[0] * v.data[2],
                                         data[0] * v.data[1] - data[1] * v.data[0]});
    return result;
}

template<class T>
typename MyVector<T>::value_type &MyVector<T>::operator[](size_type i) {
    if (i < 0 || i >= dim) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

template<class T>
const typename MyVector<T>::value_type &MyVector<T>::operator[](size_type i) const {
    if (i < 0 || i >= dim) {
        throw std::out_of_range("Index out of range");
    }
    return data[i];
}

template<class T>
typename MyVector<T>::size_type MyVector<T>::getDim() const {
    return dim;
}

template<class T>
void MyVector<T>::checkDim(const MyVector &v) const noexcept(false) {
    if (dim != v.dim) {
        throw std::invalid_argument("Dimension mismatch");
    }

}


#endif //MYVECTOR_MYVECTOR_H
