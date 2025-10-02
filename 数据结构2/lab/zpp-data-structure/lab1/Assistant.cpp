//
// Created by 邱姜铭 on 2024/3/20.
//
#ifdef _WIN32
#define CLEAR system("CLS");
#define PAUSE system("pause");
#endif
#if defined( __APPLE__) || defined(__linux__)
#define PAUSE cout << "Please press any key to continue..." << endl;\
              system("read");
#define CLEAR system("clear");
#endif

#ifdef _WIN32
#include "windows.h"
#undef min
#undef max
#define print_red(str) "";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED); std::cout << str; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);std::cout
#define print_green(str) "";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); std::cout << str; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);std::cout
#define print_yellow(str) "";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN); std::cout << str; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);std::cout
#else
#define print_red(str) "\033[31m" << str << "\033[0m"
#define print_green(str) "\033[32m" << str << "\033[0m"
#define print_yellow(str) "\033[33m" << str << "\033[0m"
#endif