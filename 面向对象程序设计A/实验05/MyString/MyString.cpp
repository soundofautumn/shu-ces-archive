//
// Created by 邱姜铭 on 2023/9/27.
//

#include "MyString.h"


MyString::MyString() {
    this->size = 0;
    this->data = new char{};
}

MyString::MyString(const MyString &string) {
    this->size = string.size;
    this->data = new char[this->size];
    for (int i = 0; i < this->size; ++i) {
        this->data[i] = string.data[i];
    }
}

MyString::MyString(MyString &&string) noexcept {
    this->size = string.size;
    this->data = string.data;
    string.data = nullptr;
    string.size = 0;
}

MyString::MyString(const char *c_str, int size) {
    if (c_str == nullptr || size == 0) {
        this->size = 0;
        this->data = new char{};
    } else {
        this->size = size;
        this->data = new char[this->size];
        for (int i = 0; i < this->size; ++i) {
            this->data[i] = c_str[i];
        }
    }
}

MyString::~MyString() {
    delete[] this->data;
}

MyString &MyString::operator=(const MyString &string) {
    if (this == &string) {
        return *this;
    }
    delete[] this->data;
    this->size = string.size;
    this->data = new char[this->size];
    for (int i = 0; i < this->size; ++i) {
        this->data[i] = string.data[i];
    }
    return *this;
}

std::ostream &MyString::operator<<(std::ostream &os) const {
    for (int i = 0; i < this->size; ++i) {
        os << this->data[i];
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const MyString &string) {
    return string.operator<<(os);
}

const char *MyString::c_str() const {
    char *temp = new char[this->size + 1];
    for (int i = 0; i < this->size; ++i) {
        temp[i] = this->data[i];
    }
    temp[this->size] = '\0';
    return temp;
}

MyString &MyString::operator+(const MyString &string) const {
    auto *temp = new MyString();
    temp->size = this->size + string.size;
    temp->data = new char[temp->size];
    for (int i = 0; i < this->size; ++i) {
        temp->data[i] = this->data[i];
    }
    for (int i = 0; i < string.size; ++i) {
        temp->data[this->size + i] = string.data[i];
    }
    return *temp;
}

MyString &MyString::operator+=(const MyString &string) {
    char *temp = new char[this->size];
    for (int i = 0; i < this->size; ++i) {
        temp[i] = this->data[i];
    }
    for (int i = 0; i < string.size; ++i) {
        temp[this->size + i] = string.data[i];
    }
    delete[] this->data;
    this->size += string.size;
    this->data = temp;
    return *this;
}

bool MyString::operator==(const MyString &string) const {
    return *this - string == 0;
}

bool MyString::operator<(const MyString &string) const {
    return *this - string < 0;
}

bool MyString::operator>(const MyString &string) const {
    return *this - string > 0;
}

bool MyString::operator<=(const MyString &string) const {
    return *this - string <= 0;
}

bool MyString::operator>=(const MyString &string) const {
    return *this - string >= 0;
}

bool MyString::operator!=(const MyString &string) const {
    return *this - string != 0;
}

char MyString::operator[](int index) const noexcept(false) {
    if (index < 0 || index >= this->size) {
        throw std::out_of_range("Index out of range");
    }
    return this->data[index];
}

int MyString::operator-(const MyString &string) const {
    if (this == &string) {
        return 0;
    }
    if (this->size != string.size) {
        return this->size - string.size;
    }
    for (int i = 0; i < this->size; ++i) {
        if (this->data[i] != string.data[i]) {
            return this->data[i] - string.data[i];
        }
    }
    return 0;
}

int MyString::length() const {
    return this->size;
}
