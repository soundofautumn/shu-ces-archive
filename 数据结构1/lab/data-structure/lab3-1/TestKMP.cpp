#include <string>
#include "KMP.h"              // KMP算法

int main() {    // 测式KMP字符串模式匹配算法
#ifdef _WIN32
    system("chcp 65001");   // 设置字符集为UTF-8
#endif
    String ob, pat;         // 主串和模式串

    cout << "请依次输入主串和模式串：" << endl;
    // 读入主串和模式串 各串以回车结束
    std::string str;
    getline(cin, str);
    ob = str.c_str();
    getline(cin, str);
    pat = str.c_str();

    cout << "主串为：";
    Write(ob);
    cout << "模式串为：";
    Write(pat);

    cout << endl << "从主串开始位置（第0个字符）查找模式串：";
    cout << KMP_find(ob, pat) << endl;

    cout << endl << "从主串第3个字符开始查找模式串：";
    cout << KMP_find(ob, pat, 3) << endl;

    pat = "string";
    cout << endl << "改模式串为string，从主串开始位置查找模式串：";
    cout << KMP_find(ob, pat) << endl;

    pat = "this";
    cout << endl << "改模式串为this，从主串开始位置查找模式串：";
    cout << KMP_find(ob, pat) << endl;

    cout << endl << "改模式串为this，从主串第1个字符开始查找模式串：";
    cout << KMP_find(ob, pat, 1) << endl;

    pat = "that";
    cout << endl << "改模式串为that，从主串开始位置查找模式串：";
    cout << KMP_find(ob, pat) << endl;

    pat = "this is a string!";
    cout << endl << "改模式串为this is a string!，从主串开始位置查找模式串：";
    cout << KMP_find(ob, pat) << endl;

    pat = ob;
    cout << endl << "改模式串为this is a string，从主串开始位置查找模式串：";
    cout << KMP_find(ob, pat) << endl;

    // 测试KMP_find_all
    int *pos;
    ob = "this is a string";
    pat = "is";
    cout << endl << "改模式串为is，从主串开始位置查找模式串：";
    cout << KMP_find_all(ob, pat, pos) << endl;
    cout << "模式串is在主串中出现的位置为：";
    for (int i = 0; i < KMP_find_all(ob, pat, pos); i++)
        cout << pos[i] << " ";
    cout << endl;

#ifdef _WIN32
    system("PAUSE");        // 调用库函数system()
#endif
#if defined( __APPLE__) || defined(__linux__)
    cout << "Please press any key to continue..." << endl;
    system("read");
#endif
    return 0;               // 返回值0, 返回操作系统
}
