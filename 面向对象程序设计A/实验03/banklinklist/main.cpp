#include<iostream>
#include"UserList.h"

using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void user_process();

void admin_process();

UserList Bank = UserList();
char choice;

int main() {
    while (true) {
        cout << "您是用户还是管理员？\n1、用户；2、管理员\n";

        cin >> choice;
        switch (choice) {
            case '1':
                user_process();
                break;
            case '2':
                admin_process();
                break;
            default:
                cout << "系统已经退出" << endl;
                return 0;
        }
    }
}

void user_process() {
    string name;
    cout << "输入用户名：";
    cin >> name;
    if (!Bank.contain_user(name)) {
        cout << "没有找到此用户\n";
        return;
    }
    auto *p = Bank.find_user(name);
    while (true) {
        cout << "您的账户名为：" << name << endl;
        cout << "请问您想办理什么业务？\n1、存款；2、取款；3、开户；4、销户；5、查询账目余额\n";
        cin >> choice;
        double num;
        string acc_name;
        switch (choice) {
            case '1':
                cout << "请输入存入的账户名：";
                cin >> acc_name;
                cout << "请输入金额：";
                cin >> num;
                p->account->change_by_name(acc_name, num, true);
                system(CLEAR);
                break;
            case '2':
                cout << "请输入取出的账户名：";
                cin >> acc_name;
                cout << "请输入金额：";
                cin >> num;
                p->account->change_by_name(acc_name, num, false);
                system(CLEAR);
                break;
            case '3':
                cout << "请输入想设置的的账户名：";
                cin >> acc_name;
                cout << "请输入金额：";
                cin >> num;
                p->account->insert(acc_name, num);
                system(CLEAR);
                break;

            case '4':
                cout << "输入要删除的账目名：";
                cin >> acc_name;
                p->account->delete_by_name(acc_name);
                system(CLEAR);
                break;

            case '5':
                cout << "\t账户\t余额\n";
                p->account->print_property();
                break;
            default:
                return;
        }
    }
}

void admin_process() {
    while (true) {
        cout << "您要做什么工作？\n"
             << "1、查看所有用户资产明细；2、新增用户；3、删除用户\n";
        cin >> choice;
        string name;
        switch (choice) {
            case '1':
                Bank.query_all();
                break;
            case '2':
                cout << "输入新增用户名称：\n";
                cin >> name;
                Bank.insert_user(name, new Account());
                system(CLEAR);
                break;
            case '3':
                cout << "输入要删除的用户名称：\n";
                cin >> name;
                Bank.delete_user(name);
                system(CLEAR);
                break;
            default:
                return;
        }
    }
}