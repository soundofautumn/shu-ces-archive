// C-String.h
#ifndef C_STRING_H
#define C_STRING_H

// 自定义版C-字符串基本处理函数
int StrLen(const char* str);
char* StrCpy(char* dest, const char* source);
char* StrCat(char* str1, const char* str2);
int StrCmp(const char* str1, char* str2);
int AtoI(const char* str);
void swap(char* str1, char*  str2);		// 重载C++系统提供的函数模板

// 堆中字符串容量的自动扩展方法
char* GetHeapString(char*& str, const char* source);
void FreeHeapString(char*& str);

#endif
