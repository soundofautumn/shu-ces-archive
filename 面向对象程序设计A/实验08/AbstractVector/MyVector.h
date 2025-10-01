//
// Created by 邱姜铭 on 2023/10/19.
//

#ifndef ABSTRACTVECTOR_MYVECTOR_H
#define ABSTRACTVECTOR_MYVECTOR_H

#include <iostream>

template<typename T>
class MyVector {
public:
    typedef T value_type;
    typedef int size_type;

    MyVector() : size(0), data(nullptr) {};

    MyVector(value_type *&&data, size_type size);

    MyVector(const value_type *data, size_type size);

    explicit MyVector(MyVector *v) : MyVector(*v) {};

    MyVector(const MyVector &v);

    MyVector(MyVector &&v) noexcept;

    // 虚析构函数
    virtual ~MyVector() = default;

    void resize(size_type new_size);

    MyVector &operator=(const MyVector &v);

    MyVector &operator=(MyVector &&v) noexcept;

    bool operator==(const MyVector &v) const;

    bool operator!=(const MyVector &v) const;

    void append(const MyVector &v);

    value_type &operator[](size_type index);

    // 虚函数 清空数据
    virtual void clear();

    // 纯虚函数 转换为字符串
    [[nodiscard]] virtual const char *toString() const = 0;

    [[nodiscard]] size_type getSize() const {
        return size;
    }

protected:
    size_type size{};
    value_type *data;
};

template<typename T>
MyVector<T>::MyVector(value_type *&&data, size_type size) {
    this->size = size;
    this->data = data;
    size = 0;
    data = nullptr;
}

template<typename T>
MyVector<T>::MyVector(const value_type *data, size_type size) {
    this->size = size;
    this->data = new value_type[size];
    for (int i = 0; i < size; ++i) {
        this->data[i] = data[i];
    }
}

template<typename T>
MyVector<T>::MyVector(const MyVector &v) {
    this->size = v.size;
    this->data = new value_type[size];
    for (int i = 0; i < size; ++i) {
        this->data[i] = v.data[i];
    }
}

template<typename T>
MyVector<T>::MyVector(MyVector &&v) noexcept {
    this->size = v.size;
    this->data = v.data;
    v.size = 0;
    v.data = nullptr;
}

template<typename T>
void MyVector<T>::resize(size_type new_size) {
    if (new_size < 0) {
        throw std::invalid_argument("new_size must be positive");
    }
    if (new_size == size) {
        return;
    }
    auto *new_data = new value_type[new_size];
    for (int i = 0; i < new_size; ++i) {
        if (i < size) {
            new_data[i] = data[i];
        } else {
            new_data[i] = 0;
        }
    }
    delete[] data;
    data = new_data;
    size = new_size;
}

template<typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector &v) {
    if (this == &v) {
        return *this;
    }
    delete[] data;
    this->size = v.size;
    this->data = new value_type[size];
    for (size_type i = 0; i < size; ++i) {
        this->data[i] = v.data[i];
    }
    return *this;
}

template<typename T>
MyVector<T> &MyVector<T>::operator=(MyVector<T> &&v) noexcept {
    if (this == &v) {
        return *this;
    }
    this->size = v.size;
    this->data = v.data;
    v.size = 0;
    v.data = nullptr;
    return *this;
}

template<typename T>
bool MyVector<T>::operator==(const MyVector &v) const {
    if (this == &v) {
        return true;
    }
    if (this->size != v.size) {
        return false;
    }
    for (size_type i = 0; i < size; ++i) {
        if (this->data[i] != v.data[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector &v) const {
    return !operator==(v);
}

template<typename T>
void MyVector<T>::append(const MyVector &v) {
    resize(size + v.size);
    for (int i = 0; i < v.size; ++i) {
        data[i + size - v.size] = v.data[i];
    }
}

template<typename T>
typename MyVector<T>::value_type &MyVector<T>::operator[](MyVector::size_type index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
void MyVector<T>::clear() {
    delete[] data;
    data = nullptr;
    size = 0;
}

#endif //ABSTRACTVECTOR_MYVECTOR_H
