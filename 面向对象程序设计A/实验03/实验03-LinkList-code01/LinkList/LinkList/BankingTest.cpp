// BankingTest.cpp
#include "LinkList.h"
#include "Banking.h"

#ifdef _MSC_VER
#include <conio.h>
#else
#define getche() cin.get()
#endif

void BankingTest() {
    LinkList<User> uLink;
    User xUser;
    Node<User> *pU;
    BWB xBWB;
    char id[80], name[80], str[80];
    int choice, year, month, day;
    double money;

    while (true) {
        cout << "\n请输入账号(n账号--开户，直接回车则退出)：";
        cin.getline(id, 80);
        if (id[0] == '\0')
            break;
        if (id[0] == 'N' || id[0] == 'n') {
            cout << "请输入户名：";
            cin.getline(name, 80);
            xUser.Set(id + 1, name);
            uLink.Append(xUser);
        } else
            xUser.Set(id, "");
        pU = uLink.Locate(string(xUser), true);
        if (pU == NULL) {
            cout << "账号输入错误！" << endl;
            continue;
        }

        while (true) {
            cout << endl;
            uLink.CurData().Show(cout);
            cout << "1 -- 存入（正数）/支取（负数）" << endl;
            cout << "2 -- 查询" << endl;
            cout << "0 -- 返回" << endl;
            cout << "请选择：";
            choice = getche() - '0';
            cout << endl;
            if (choice <= 0) break;
            switch (choice) {
                case 1:
                    cout << "请输入（年 月 日 金额）: ";
                    cin >> year >> month >> day >> money;
                    cin.getline(str, 80);                    // 处理换行字符
                    xBWB.Set(year, month, day, money);
                    uLink.CurData().AppendBWB(xBWB);
                    break;
                case 2:
                    cout << uLink.CurData() << endl;
                    break;
            }
        }
    }
    cout << "\n自动调用析构函数释放所有结点，返回主函数。\n" << endl;
}
