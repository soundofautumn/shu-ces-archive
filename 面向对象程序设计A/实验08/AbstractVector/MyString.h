//
// Created by 邱姜铭 on 2023/10/19.
//

#ifndef ABSTRACTVECTOR_MYSTRING_H
#define ABSTRACTVECTOR_MYSTRING_H

#include <string>
#include "MyVector.h"

class MyString : public MyVector<char> {
public:
    MyString();

    explicit MyString(const std::string &str);

    explicit MyString(std::string &&str);

    MyString(const char *c_str, int length);

    MyString(const MyString &str);

    MyString(MyString &&str) noexcept;

    ~MyString() override = default;

    MyString &operator=(const MyString &str);

    MyString &operator=(MyString &&str) noexcept;

    bool operator==(MyString const &string) const;

    bool operator!=(MyString const &string) const;

    bool operator<(MyString const &string) const;

    bool operator>(MyString const &string) const;

    bool operator<=(MyString const &string) const;

    bool operator>=(MyString const &string) const;

    void push_back(char i);

    std::ostream &operator<<(std::ostream &os) const;

    friend std::ostream &operator<<(std::ostream &os, MyString const &string);

    std::istream &operator>>(std::istream &is);

    friend std::istream &operator>>(std::istream &is, MyString &string);

    MyString operator+(const MyString &str) const;

    MyString &operator+=(const MyString &str);

    [[nodiscard]] const char *c_str() const;

    [[nodiscard]] const char *toString() const override;

    void clear() override;

private:
    // c_str_temp is used to store the c_str() result
    const char *c_str_temp = nullptr;

    // clear c_str_temp
    void clear_c_str_temp();

    int operator-(MyString const &string) const;
};


#endif //ABSTRACTVECTOR_MYSTRING_H
