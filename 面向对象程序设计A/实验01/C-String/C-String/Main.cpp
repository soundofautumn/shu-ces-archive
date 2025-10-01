// Main.cpp
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>                    // for atoi

#ifdef _MSC_VER
#include <conio.h>
#endif

#include "C-String.h"
#include "SortStrings.h"

using namespace std;

// 自定义版C-字符串处理函数测试，并与标准C-字符串处理函数比较
void TestStr() {
    char str[][20] = {"", "abc", "abcd", "上海大学"};
    char s0[80], s1[80];
    int n = sizeof(str) / sizeof(*str);

    cout << "\n【自定义版C-字符串处理函数测试，并与标准C-字符串处理函数比较】";
    for (int i = 0; i < n; i++) {
        cout << "\nStrLen(\"" << str[i] << "\") : " << StrLen(str[i]);
        cout << "\nstrlen(\"" << str[i] << "\") : " << strlen(str[i]) << endl;

        cout << "\nStrCpy(s0, \"" << str[i] << "\") : \"" << StrCpy(s0, str[i]) << "\"";
        cout << "\nstrcpy(s1, \"" << str[i] << "\") : \"" << strcpy(s1, str[i]) << "\"";
        cout << "\nstrcmp(s0, s1) : " << strcmp(s0, s1) << "\t【0表示正确，非零表示出错】" << endl;

        cout << "\nStrCat(s0, \"" << str[i] << "\") : \"" << StrCat(s0, str[i]) << "\"";
        cout << "\nstrcat(s1, \"" << str[i] << "\") : \"" << strcat(s1, str[i]) << "\"";
        cout << "\nstrcmp(s0, s1) : " << strcmp(s0, s1) << "\t【0表示正确，非零表示出错】" << endl;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "\nStrCmp(\"" << str[i] << "\", \"" << str[j] << "\") : " << StrCmp(str[i], str[j]);
            cout << "\nstrcmp(\"" << str[i] << "\", \"" << str[j] << "\") : " << strcmp(str[i], str[j]) << endl;
        }
    }
}

// 自定义AtoI函数测试，并与标准函数atoi比较
void TestAtoI() {
    char str[][20] = {" +12345", "+ 12345", " 12345", "		- 123", "	  -123", " 123.45", "+123abc", "", "-abc",
                      "+ABC"};
    int n = sizeof(str) / sizeof(*str), x, y, q, err = 0;

    cout << "\n【测试AtoI，并与标准函数atoi比较】" << endl;
    for (int i = 0; i < n; i++) {
        x = AtoI(str[i]);
        y = atoi(str[i]);
        q = x - y;
        if (q < 0) q = -q;
        if (q > err) err = q;
        cout << "AtoI(\"" << str[i] << "\") : " << x << endl;
        cout << "atoi(\"" << str[i] << "\") : " << y << ",\t" << (x == y ? "正确" : "错误") << endl;
    }
    cout << "最大误差: " << err << endl;
}

// C-字符串交换测试
void TestSwap() {
    char array1[20] = "Tom", array2[20] = "Jerry";        // 字符型数组作为C-字符串的容器
    const char *p1 = "Snoopy", *p2 = "Winnie";            // 指针指向字符串常量（常量数组的首地址）
    cout << "\n【C-字符串交换测试】" << endl;
    cout << "交换前\tarray1: \"" << array1 << "\",\tarray2: \"" << array2 << "\"" << endl;
    swap(array1, array2);
    cout << "交换后\tarray1: \"" << array1 << "\",\tarray2: \"" << array2 << "\"" << endl;

    cout << "\n交换前\tp1: \"" << p1 << "\",\tp2: \"" << p2 << "\"" << endl;
    swap(p1, p2);
    cout << "交换后\tp1: \"" << p1 << "\",\tp2: \"" << p2 << "\"" << endl;
}

// 堆中字符串容量的自动扩展方法
void TestHeapString() {
    char *str = NULL;                                            // 18. 此处为什么要将str初始化为NULL，否则会发生什么情况？
    char s[1024];
    cout << "\"" << GetHeapString(str, "Hello") << "\"" << endl;
    cout << "\"" << GetHeapString(str, " world!") << "\"" << endl;
    FreeHeapString(str);
    cout << GetHeapString(str,
                          "请输入一个字符串: ");            // 19. 每执行一次GetHeapString或FreeHeapString函数，str的指向是否发生变化？
    cin.getline(s, 1024);
    cout << "\"" << GetHeapString(str, s) << "\"" << endl;
    FreeHeapString(str);
}

// 多种存储方式的C-字符串数组排序测试
void TestSortStrings() {
    // 每个字符串固定占用NUM长度
    char strA[][NUM] = {"enter", "number", "C/C++程序设计", "size", "指针", "begin", "of", "函数", "cat", "case",
                        "program", "certain", "a", "cake", "side"};
    // 每个字符串占有实际长度 字面量字符串应用const char * 这里隐式转换成了 char *
    // 试图写入时可能导致运行错误
    char *strB[] = {"enter", "number", "C/C++程序设计", "size", "指针", "begin", "of", "函数", "cat", "case", "program",
                    "certain", "an", "cake", "side"};
    // 每个字符串占有实际长度
    const char *strB0[] = {"enter", "number", "C/C++程序设计", "size", "指针", "begin", "of", "函数", "cat", "case",
                           "program", "certain", "an", "cake", "side"};
    char **strC = NULL, **strD = NULL, **strE = NULL;
    int n1 = sizeof(strA) / sizeof(*strA), n2 = sizeof(strB) / sizeof(*strB), n0 = sizeof(strB0) / sizeof(*strB0);

    cout << "\n【多种存储方式的C-字符串数组排序测试】" << endl;
    // 20. 请尝试先给出如下输出结果，再运行程序验证你的结论
    cout << "sizeof(strA) : " << sizeof(strA) << " Bytes,\tsizeof(*strA) : " << sizeof(strA[0]) << " Bytes,\tn1 = "
         << n1
         << "\nsizeof(strB) : " << sizeof(strB) << " Bytes,\tsizeof(*strB) : " << sizeof(strB[0]) << " Bytes,\tn2 = "
         << n2 << endl;
    cout << "\nsizeof(strC) : " << sizeof(strC) << " Bytes"
         << "\nsizeof(strD) : " << sizeof(strD) << " Bytes"
         << "\nsizeof(strE) : " << sizeof(strE) << " Bytes" << endl;

    GetStrings0(strC, strB0, n0);
    GetStrings1(strD, strB0, n0);
    GetStrings2(strE, strB0, n0);
    //至此，多种存储方式的字符串数组已经全部构造完成。
    // 21. 请分别画出strA，strB，strC，strD，strE的结构图，指出它们所在的空间（常量池、栈区、堆区）

    ShowStrings("\nstrA 数据: ", strA, n1);
//	BubbleB(strA, n1);											// 22. 此处为什么不能用BubbleB函数？
    BubbleA(strA, n1);
    ShowStrings("A排序结果: ", strA, n1);

    ShowStrings("\nstrB 数据: ", strB, n2);
//	BubbleA(strB, n2);											// 23. 此处为什么不能用BubbleA函数？（编译能通过，但运行时错）
    BubbleB(strB, n2);
    ShowStrings("B排序结果: ", strB, n2);

    ShowStrings("\nstrC 数据: ", strC, n0);
    BubbleB(strC, n0);                                            // 24. 此处为什么能用BubbleB函数？strC[0]是否被改变？
    ShowStrings("B排序结果: ", strC, n0);
    FreeStrings(strC, n0, true);                                // 25. 释放StrC的资源，为什么第三个参数不能采用其默认值false？
    GetStrings0(strC, strB0, n0);                // 重新构造无序的StrC
    ShowStrings("strC 数据: ", strC, n0);
    BubbleA(strC, n0);                                            // 26. 此处为什么要用BubbleA函数？strC[0]是否被改变？strC[0]的内容是否被改变？
    ShowStrings("A排序结果: ", strC, n0);

    ShowStrings("\nstrD 数据: ", strD, n0);
    BubbleA(strD, n0);                                            // 27. 此处为什么既可以用BubbleA，又可以用BubbleB函数？
    ShowStrings("A排序结果: ", strD, n0);
    FreeStrings(strD, n0);
    GetStrings1(strD, strB0, n0);
    ShowStrings("strD 数据: ", strD, n0);
    BubbleB(strD, n0);
    ShowStrings("B排序结果: ", strD, n0);

    ShowStrings("\nstrE 数据: ", strE, n0);
    BubbleB(strE, n0);                                            // 28. 此处为什么不能用BubbleA函数？
    ShowStrings("B排序结果: ", strE, n0);

    FreeStrings(strE, n0);                                        // 29. 此处是否可以写成FreeStrings(strE, n0, false);？
    FreeStrings(strD, n0);
    FreeStrings(strC, n0, true);                                // 30. 此处是否可以写成FreeStrings(strC, 1);？
}

// C-字符串超容量（下标越界）情况
void Testing() {
    unsigned long x = 1234567890;
    char str[5];
    unsigned long y = x;
    int m = uint64_t(&y) - uint64_t(str), n = uint64_t(str) - uint64_t(&x);
    cout << "&x = " << hex << uint64_t(&x) << ",\tp = " << uint64_t(str) << ",\t&y = " << uint64_t(&y)
         << ",\t间隔 " << dec << n << ",\t" << m << " 字节" << endl;

    n = (n < 0) ? -n : m;                    // 考虑到不同的编译器将变量在内存中的存放顺序不同

    cout << "x = " << x << ", y = " << y << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\n循环2次。请输入一个字符串（字符串的长度分别(1)小于" << n
             << "; (2)大于或等于" << n << "）: " << endl;
        cin.getline(str, 80);
        cout << "输入长度为 " << strlen(str) << " 字节的字符串str，请观察变量 x 和 y 是否有" << endl;
        cout << "x = " << x << ", y = " << y << ", str = \"" << str << "\"" << endl;
        cout << "恢复变量 x 和 y 的原值，请观察字符串 str 是否有变化" << endl;
        x = y = 1234567890;
        cout << "x = " << x << ", y = " << y << ", str = \"" << str << "\"" << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n1. C-字符串基本处理函数测试"
             << "\n2. C-字符串转整数 AtoI 测试"
             << "\n3. C-字符串交换测试"
             << "\n4. C-字符串数组排序测试"
             << "\n5. 堆中C-字符串容器的自动扩展测试"
             << "\n6. C-字符串下标越界示例"
             << "\n0. 退出" << endl;
#ifdef _MSC_VER
        choice = getche();
#else
        cin >> choice;
#endif
        cout << endl;
        if (choice <= 0) break;
        switch (choice) {
            case 1:
                TestStr();
                break;
            case 2:
                TestAtoI();
                break;
            case 3:
                TestSwap();
                break;
            case 4:
                TestSortStrings();
                break;
            case 5:
                TestHeapString();
                break;
            case 6:
                Testing();
                break;
        }
    }
    return 0;
}
