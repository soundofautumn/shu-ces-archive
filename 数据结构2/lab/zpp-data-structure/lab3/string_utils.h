//
// Created by 邱姜铭 on 2024/4/17.
//

#ifndef ZPP_DATA_STRUCTURE_STRING_UTILS_H
#define ZPP_DATA_STRUCTURE_STRING_UTILS_H

#include <string>
#include <codecvt>
#include <locale>

const static std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>);

#endif //ZPP_DATA_STRUCTURE_STRING_UTILS_H
