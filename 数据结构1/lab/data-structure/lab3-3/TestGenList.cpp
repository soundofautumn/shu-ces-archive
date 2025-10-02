#include "GenList.h"            // 广义表

int main() {
#ifdef _WIN32
    system("chcp 65001");   // 设置字符集为UTF-8
#endif
    GenList<char> g, g1;
    char e;
    int c = -1;
    int i;
    std::string str;
    GenList<char> p;

    while (c != 0) {
        cout << endl << "1. 生成广义表.";
        cout << endl << "2. 显示广义表.";
        cout << endl << "3. 在表头插入原子元素.";
        cout << endl << "4. 在表头插入子表元素.";
        cout << endl << "5. 删除元素.";
        cout << endl << "6. 求广义表的深度.";
        cout << endl << "7. 求广义表的长度.";
        cout << endl << "8. 在任意位置插入原子元素.";
        cout << endl << "9. 在任意位置插入子表元素.";
        cout << endl << "10. 反转广义表.";
        cout << endl << "11. 取广义表表头和表尾.";
        cout << endl << "0. 退出";
        cout << endl << "选择功能(0~10):";
        cin >> c;
        switch (c) {
            case 1:
                GetChar();                // 读入输入的回车符
                cout << "请输入广义表eg: (a,(b,c)):";
                g.Input();
                break;
            case 2:
                if (!g.IsEmpty()) {
                    g.Show();
                    cout << endl;
                } else
                    cout << "广义表为空表。" << endl;
                break;
            case 3:
                cout << endl << "输入原子元素:";
                cin >> e;
                g.Insert(e);
                break;
            case 4:
                GetChar();                // 读入输入的回车符
                cout << "请输入子表eg: (a,(b,c)):";
                g1.Input();
                g.Insert(g1);
                break;
            case 5:
                cout << endl << "输入位置:";
                cin >> i;
                if (g.Delete(i) == RANGE_ERROR)
                    cout << "位置范围错." << endl;
                break;
            case 6:
                cout << endl << "深度为:" << g.GetDepth() << endl;
                break;
            case 7:
                cout << endl << "长度为:" << g.GetLength() << endl;
                break;
            case 8:
                cout << endl << "输入原子元素:";
                cin >> e;
                cout << endl << "输入位置:";
                cin >> i;
                if (g.Insert(e, i) == RANGE_ERROR)
                    cout << "位置范围错." << endl;
                break;
            case 9:
                GetChar();                // 读入输入的回车符
                cout << "请输入子表eg: (a,(b,c)):";
                g1.Input();
                cout << endl << "输入位置:";
                cin >> i;
                if (g.Insert(g1, i) == RANGE_ERROR)
                    cout << "位置范围错." << endl;
                break;
            case 10:
                g.Reverse();
                break;
            case 11:
                cout << "请输入查询语句eg: (THT):";
                cin >> str;
                if (str[0] == 'T')
                    p = g.GetTail();
                else if (str[0] == 'H')
                    p = g.GetHead();
                else {
                    cout << "查询语句错误" << endl;
                    break;
                }
                for (int j = 1; j < str.length(); j++) {
                    if (str[j] == 'T') {
                        p = p.GetTail();
                    } else if (str[j] == 'H') {
                        p = p.GetHead();
                    } else {
                        cout << "查询语句错误" << endl;
                        break;
                    }
                }
                cout << "查询结果为:";
                p.Show();
                cout << endl;
                break;
            case 0:
            default:
                break;
        }
    }

#ifdef _WIN32
    system("PAUSE");        // 调用库函数system()
#endif
#if defined( __APPLE__) || defined(__linux__)
    cout << "Please press any key to continue..." << endl;
    system("read");
#endif
    return 0;               // 返回值0, 返回操作系统
}


