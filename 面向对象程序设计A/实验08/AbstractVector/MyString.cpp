//
// Created by 邱姜铭 on 2023/10/19.
//
#include "MyString.h"

MyString::MyString(const std::string &str) : MyVector<char>(str.c_str(), str.length()) {}

MyString::MyString(std::string &&str) : MyVector<char>(str.c_str(), str.length()) {}

MyString::MyString(const char *c_str, int length) : MyVector<char>(c_str, length) {}

MyString::MyString(const MyString &str) = default;

MyString::MyString(MyString &&str) noexcept: MyVector<char>(std::move(str)) {}

MyString::MyString() : MyVector<char>() {}

MyString &MyString::operator=(const MyString &str) = default;

MyString &MyString::operator=(MyString &&str) noexcept = default;

void MyString::push_back(char i) {
    clear_c_str_temp();
    resize(size + 1);
    data[size - 1] = i;
}

MyString MyString::operator+(const MyString &str) const {
    MyString new_str(*this);
    new_str.append(str);
    return new_str;
}

MyString &MyString::operator+=(const MyString &str) {
    clear_c_str_temp();
    append(str);
    return *this;
}

void MyString::clear_c_str_temp() {
    if (c_str_temp != nullptr) {
        delete[] c_str_temp;
        c_str_temp = nullptr;
    }
}

const char *MyString::c_str() const {
    if (c_str_temp != nullptr) {
        return c_str_temp;
    }
    char *c_str = new char[size + 1];
    for (int i = 0; i < size; ++i) {
        c_str[i] = data[i];
    }
    c_str[size] = '\0';
    return c_str;
}

const char *MyString::toString() const {
    return c_str();
}

void MyString::clear() {
    clear_c_str_temp();
    MyVector<char>::clear();
}

std::ostream &MyString::operator<<(std::ostream &os) const {
    os << toString();
    return os;
}

std::ostream &operator<<(std::ostream &os, const MyString &string) {
    string.operator<<(os);
    return os;
}

std::istream &MyString::operator>>(std::istream &is) {
    clear_c_str_temp();
    char c;
    while (is.get(c)) {
        if (c == '\n') {
            break;
        }
        this->push_back(c);
    }
    return is;
}

std::istream &operator>>(std::istream &is, MyString &string) {
    string.operator>>(is);
    return is;
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

bool MyString::operator==(const MyString &string) const {
    return this->operator-(string) == 0;
}

bool MyString::operator!=(const MyString &string) const {
    return this->operator-(string) != 0;
}

bool MyString::operator<(const MyString &string) const {
    return this->operator-(string) < 0;
}

bool MyString::operator>(const MyString &string) const {
    return this->operator-(string) > 0;
}

bool MyString::operator<=(const MyString &string) const {
    return this->operator-(string) <= 0;
}

bool MyString::operator>=(const MyString &string) const {
    return this->operator-(string) >= 0;
}




