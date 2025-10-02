//
// Created by 邱姜铭 on 2024/4/18.
//

#ifndef ZPP_DATA_STRUCTURE_CONSOLE_UTILS_H
#define ZPP_DATA_STRUCTURE_CONSOLE_UTILS_H

#ifdef _WIN32
#define CLEAR (void) system("cls");
#define PAUSE (void) system("pause");
#endif
#if defined( __APPLE__) || defined(__linux__)
#define PAUSE cout << "Please press any key to continue..." << endl;\
              (void)! system("read");
#define CLEAR (void)! system("clear");
#endif

#include <type_traits>
#include <string>
#include <iostream>

template<class STR, class Char_t>
struct is_string_of : std::false_type {
};

template<class STR, class Char_t>
struct is_string_of<const STR, Char_t> : is_string_of<STR, Char_t> {
};

template<class STR, class Char_t>
struct is_string_of<STR &, Char_t> : is_string_of<STR, Char_t> {
};

template<class Char_t>
struct is_string_of<std::basic_string<Char_t>, Char_t> : std::true_type {
};

template<class Char_t>
struct is_string_of<const Char_t *, Char_t> : std::true_type {
};

template<class Char_t>
struct is_string_of<Char_t *, Char_t> : std::true_type {
};

template<class STR>
using is_wstring = is_string_of<STR, wchar_t>;

template<class STR>
using is_string = is_string_of<STR, char>;

static_assert(is_string<std::string>::value, "is_string<std::string> should be true");
static_assert(is_string<const std::string>::value, "is_string<const std::string> should be true");
static_assert(is_string<const std::string &>::value, "is_string<const std::string &> should be true");
static_assert(is_string<char *>::value, "is_string<char *> should be true");
static_assert(is_string<const char *>::value, "is_string<const char *> should be true");

static_assert(is_wstring<std::wstring>::value, "is_wstring<std::wstring> should be true");
static_assert(is_wstring<const std::wstring>::value, "is_wstring<const std::wstring> should be true");
static_assert(is_wstring<const std::wstring &>::value, "is_wstring<const std::wstring &> should be true");
static_assert(is_wstring<wchar_t *>::value, "is_wstring<wchar_t *> should be true");
static_assert(is_wstring<const wchar_t *>::value, "is_wstring<const wchar_t *> should be true");

#ifdef _WIN32
#define NOMINMAX
#include "windows.h"

enum class Color {
    red = FOREGROUND_RED,
    green = FOREGROUND_GREEN,
    yellow = FOREGROUND_RED | FOREGROUND_GREEN
};

#define PRINT_WITH_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color)); os << ps.str; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

#else

enum class Color {
    red = 31,
    green = 32,
    yellow = 33
};

#define PRINT_WITH_COLOR os << "\033[" << static_cast<int>(color) << "m" << ps.str << "\033[0m";

#endif

template<class STR, Color color, class = void>
struct print_string;

template<class STR, Color color>
struct print_string<STR, color, typename std::enable_if<is_string<STR>::value, void>::type> {
    const std::string &str;

    friend std::ostream &operator<<(std::ostream &os, const print_string &ps) {
        PRINT_WITH_COLOR
        return os;
    }

    explicit print_string(const std::string &str) : str(str) {}

    explicit print_string(std::string &&str) : str(std::move(str)) {}
};

template<class STR, Color color>
struct print_string<STR, color, typename std::enable_if<is_wstring<STR>::value, void>::type> {
    const std::wstring &str;

    friend std::wostream &operator<<(std::wostream &os, const print_string &ps) {
        PRINT_WITH_COLOR
        return os;
    }

    explicit print_string(const std::wstring &str) : str(str) {}

    explicit print_string(std::wstring &&str) : str(std::move(str)) {}

};

template<class STR>
print_string<typename std::decay<STR>::type, Color::red> print_red(STR &&str) {
    return print_string<typename std::decay<STR>::type, Color::red>(str);
}

template<class STR>
print_string<typename std::decay<STR>::type, Color::green> print_green(STR &&str) {
    return print_string<typename std::decay<STR>::type, Color::green>(str);
}

template<class STR>
print_string<typename std::decay<STR>::type, Color::yellow> print_yellow(STR &&str) {
    return print_string<typename std::decay<STR>::type, Color::yellow>(str);
}

#undef PRINT_WITH_COLOR

#endif //ZPP_DATA_STRUCTURE_CONSOLE_UTILS_H
