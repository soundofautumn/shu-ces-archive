// C-String.cpp
#include "C-String.h"
#include <cstring>

int StrLen(const char *str) {
    int n;
    for (n = 0; str[n] != '\0'; n++);
    return n;
}

char *StrCpy(char *dest, const char *source) {
    char *temp = dest;
    while (*dest++ = *source++)                    // 1. 请解释本循环的执行过程：何时结束循环，为什么？指针如何变化、指针的目标如何变化？
        ;
    return temp;                                // 2. 为什么要使用指针变量temp？此处能否改成return dest;？
}

char *StrCat(char *str1, const char *str2) {
    char *temp = str1;
    while (*str1)                                // 3. 本循环结束时指针str1的目标是什么字符？
        str1++;
    while (*str1++ = *str2++);
    return temp;
}

int StrCmp(const char *str1, char *str2) {
    unsigned char *p = (unsigned char *) str1;    // 4. 为什么要用另外两个指针变量p和q？
    unsigned char *q = (unsigned char *) str2;
    while (*p && *q && *p == *q)                // 5. 有哪些情况可能导致本循环结束（最好能举例说明）？
        p++, q++;
    return *p > *q ? 1 : (*p < *q ? -1 : 0);    // 6. 串结束标志字符'\0'的值等于多少，起到什么作用？
}

int AtoI(const char *str) {
    int sgn = 1, num = 0, i;
    for (i = 0; str[i] == ' ' || str[i] == '\t' || str[i] == '\n'; i++);
    if (str[i] == '+' || str[i] == '-') {
        sgn = (str[i] == '+') ? 1 : -1;
        i++;
    }
    for (; str[i]; i++) {
        if ('0' <= str[i] && str[i] <= '9')        // 7. 条件表达式是否能写成 ('0' <= str[i] <= '9') ？
            num = 10 * num + (str[i] - '0');    // 8. 表达式中为什么要减去'0'？
        else
            break;
    }
    return sgn * num;
}

void swap(char *str1, char *str2)                // 本函数重载了C++系统提供的函数模板swap
{
    char *temp = new char[StrLen(str1) + 1];
    StrCpy(temp, str1);
    StrCpy(str1, str2);
    StrCpy(str2, temp);
    delete[] temp;
}

// 堆中字符串容量的自动扩展方法
char *GetHeapString(char *&str, const char *source)    // 9. 此处为什么要设计传递指针的引用？
{
    if (str == NULL)                            // 处理特殊情况，意味着本函数可以处理空指针
    {
        str = new char[1];
        str[0] = '\0';
    }
    if (source == NULL) return str;
    char *temp = new char[strlen(str) + strlen(source) + 1];    // 申请更大的资源空间
    strcpy(temp, str);                            // 复制原有数据
    strcat(temp, source);                        // 追加新数据
    delete[] str;                                // 释放原来的资源
    str = temp;                                    // 更换为新的堆地址值
    return str;
}

void FreeHeapString(char *&str) {
    if (str != NULL)
        delete[] str;
    str = NULL;                                    // 10. 为什么要置str为NULL？
}
