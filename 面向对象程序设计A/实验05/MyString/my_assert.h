//
// Created by 邱姜铭 on 2023/10/8.
//

#ifndef MYSTRING_MY_ASSERT_H
#define MYSTRING_MY_ASSERT_H

#include <iostream>
#include <sstream>

#ifdef _WIN32
#include "windows.h"
#define print_red(str) "";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED); std::cout << str; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);std::cout
#define print_green(str) "";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); std::cout << str; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);std::cout
#define print_yellow(str) "";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN); std::cout << str; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);std::cout
#else
#define print_red(str) "\033[31m" << str << "\033[0m"
#define print_green(str) "\033[32m" << str << "\033[0m"
#define print_yellow(str) "\033[33m" << str << "\033[0m"
#endif
#define run(x) std::cout << "Running " << print_yellow(#x) << std::endl; x;

#define my_assert_throws(x, exception) \
try {                                  \
    std::cout << print_green("Expecting Exception: ") << #exception << std::endl;    \
    run(x);                                 \
    std::cout << print_red("No Exception throws Failed") << std::endl; \
} catch (exception &e) {               \
    std::cout << print_green("Exception Matched") << std::endl; \
}

#define my_assert(actual, expected) \
std::cout << print_green("Expected:") << " (" << #expected << ") " \
     << print_red("Actual:") <<" (" << print_yellow(#actual) << ")"; \
my_assert_impl<decltype(actual)>(actual, expected);         \


template<typename T>
void my_assert_impl(T actual, T expected) {
    if (actual == expected) {
        std::cout << print_green(" Passed") << std::endl;
    } else {
        std::cout << print_red(" Failed") << std::endl;
    }
}

template<typename T>
void my_assert_impl(T actual, std::string_view expected) {
    std::ostringstream oss;
    oss << actual;
    if (oss.str() == expected) {
        std::cout << print_green(" Passed") << std::endl;
    } else {
        std::cout << print_red(" Failed") << std::endl;
    }
}


#endif //MYSTRING_MY_ASSERT_H
