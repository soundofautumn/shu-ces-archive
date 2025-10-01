//
// Created by 邱姜铭 on 2023/9/27.
//

#ifndef MYSTRING_MYSTRING_H
#define MYSTRING_MYSTRING_H

#include <iostream>


class MyString {
public:

    MyString();

    MyString(const char *c_str, int length);

    MyString(MyString const &string);

    MyString(MyString &&string) noexcept;

    ~MyString();

    MyString &operator=(MyString const &string);

    std::ostream &operator<<(std::ostream &os) const;

    friend std::ostream &operator<<(std::ostream &os, MyString const &string);

    std::istream &operator>>(std::istream &is) = delete;

    friend std::istream &operator>>(std::istream &is, MyString &string) = delete;

    MyString &operator+(MyString const &string) const;

    MyString &operator+=(MyString const &string);

    bool operator==(MyString const &string) const;

    bool operator<(MyString const &string) const;

    bool operator>(MyString const &string) const;

    bool operator<=(MyString const &string) const;

    bool operator>=(MyString const &string) const;

    bool operator!=(MyString const &string) const;

    char operator[](int index) const noexcept(false) ;

    const char *c_str() const;

    int length() const;

private:
    int operator-(MyString const &string) const;

    char *data;
    int size;
};


#endif //MYSTRING_MYSTRING_H
