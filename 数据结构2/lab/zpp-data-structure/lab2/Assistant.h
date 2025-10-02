//
// Created by 邱姜铭 on 2024/4/2.
//
#ifndef ZPP_DATA_STRUCTURE_ASSISTANT_H
#define ZPP_DATA_STRUCTURE_ASSISTANT_H

#include <string>
#include <codecvt>

const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>);
const std::wstring DELIMITER = L"==========我是分割线==============";

#endif //ZPP_DATA_STRUCTURE_ASSISTANT_H
