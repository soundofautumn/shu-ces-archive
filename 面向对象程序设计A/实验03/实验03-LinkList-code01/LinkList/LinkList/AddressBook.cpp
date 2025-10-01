// AddressBook.cpp
#include "LinkList.h"
#include <iomanip>
#include <cstring>
#include <string>

#ifdef _MSC_VER
#include <conio.h>
#else
#define getche() cin.get()
#endif

class AddressBook {
public:
    AddressBook(int Id = 0, const char *Name = "NoName", const char *Phone = "", const char *Email = "") : id(Id) {
        strncpy(name, Name, sizeof(name));        // 为了安全保障，指定长度拷贝字符串
        name[sizeof(name) - 1] = '\0';            // 对可能超长的字符串进行截断
        strncpy(phone, Phone, sizeof(phone));
        phone[sizeof(phone) - 1] = '\0';
        email = Email;    // 相当于 email = string(Email); 将C-字符串Email转换成string然后再赋值。本句可移至冒号语法处
    }

    friend ostream &operator<<(ostream &out, const AddressBook &a) {
        out << setfill('0') << setw(8) << a.id << '\t' << a.name << '\t'
            << setfill(' ') << setw(11) << a.phone << '\t' << a.email;
        return out;
    }

    friend istream &operator>>(istream &in, AddressBook &a) {
        char str[80];
        in.getline(str, 80, '\t');
        a.id = atoi(str);
        in.getline(str, 80, '\t');
        strncpy(a.name, str, sizeof(a.name));
        a.name[sizeof(a.name) - 1] = '\0';
        in.getline(str, 80, '\t');
        strncpy(a.phone, str, sizeof(a.phone));
        a.phone[sizeof(a.phone) - 1] = '\0';
        in.getline(str, 80);
        a.email = str;
        return in;
    }

    operator int() const { return id; }    // 类型转换运算符，将本对象转换为 int（指编号）
    operator string() const { return name; }    // 类型转换运算符，将本对象转换为 C++字符串string（指姓名）
    operator long long() const { return atoll(phone); }    // 类型转换运算符，将本对象转换为 long long（指手机号码）
private:
    int id;
    char name[21], phone[12];
    string email;
};

template<typename T>
void Search(LinkList<AddressBook> &link, const T &t) {
    int n = 0;
    Node<AddressBook> *p;
    p = link.Locate(t, true);
    while (p != NULL) {
        n++;
        cout << link.CurData() << endl;
        p = link.Locate(t);
    }
    cout << "找到 " << n << " 个满足条件的结点" << endl;
}

void Find(LinkList<AddressBook> &link, int flag) {
    char str[80];
    switch (flag) {
        case '1':
            cout << "请输入查询的编号: ";
            cin.getline(str, 80);
            Search(link, atoi(str));
            break;

        case '2':
            cout << "请输入查询的姓名: ";
            cin.getline(str, 80);
            Search(link, string(str));
            break;

        case '3':
            cout << "请输入查询的手机号码: ";
            cin.getline(str, 80);
            Search(link, atoll(str));
            break;
    }
}

void AddressBookTest() {
    int Pos(char ch, const char *str);                        // 函数声明
    int Choice(const char *prompt, const char *options = "");    // 函数声明
    LinkList<AddressBook> link;
    char filename[80] = "AddressBook.txt";
    AddressBook x;
    int key, k, n, yn;
    n = link.Load(filename);
    cout << "\n已从 " << filename << " 文件中读取了 " << n << " 个结点的数据" << endl;

    while (true) {
        cout << "\n\n========= 通讯录 =========" << endl;
        cout << "  1 ---- 输 出 通讯录 (P)" << endl;
        cout << "  2 ---- 插入新的结点 (I)" << endl;
        cout << "  3 ---- 追加新的结点 (A)" << endl;
        cout << "  4 ---- 查        询 (S)" << endl;
        cout << "  5 ---- 倒        置 (V)" << endl;
        cout << "  6 ---- 排        序 (O)" << endl;
        cout << "  7 ---- 数据写入文件 (W)" << endl;
        cout << "  8 ---- 读取数据文件 (R)" << endl;
        cout << "  9 ---- 释放所有结点 (F)" << endl;
        cout << "  0 ---- 退      出 (ESC)" << endl;
        cout << "==========================" << endl;
        key = Choice("请选择", "0123456789\x1bpPiIaAsSvVoOwWrRfF");
        cout << "\n\n";
        if (key == 27 || key == '0')        // '\x1b'等于27，指ESC键
            break;
        switch (key) {
            case '1':
            case 'p':
            case 'P':
                cout << link << endl;
                break;
            case '2':
            case 'i':
            case 'I':
                cout << "插入一个结点到链表首结点前。" << endl;
                cout << "请输入数据域数据(编号Tab姓名Tab手机号码TabEmail换行): ";
                cin >> x;
                link.Insert(x);
                break;
            case '3':
            case 'a':
            case 'A':
                cout << "追加一个结点(至尾结点后)。";
                cout << "请输入数据域数据(编号Tab姓名Tab手机号码TabEmail换行): ";
                cin >> x;
                link.Append(x);
                break;
            case '4':
            case 's':
            case 'S':
                cout << "根据数据域数据查询。可根据如下三种方式查询。" << endl;
                cout << "1 序号，2 姓名，3 手机号码。请选择: ";
                k = getche();
                Find(link, k);
                break;
            case '5':
            case 'v':
            case 'V':
                cout << "链表所有结点倒置。倒置之前\n" << link << endl;
                link.Reverse();
                cout << "倒置之前\n" << link << endl;
                break;
            case '6':
            case 'o':
            case 'O':
                cout << "排序根据 1按序号，2按姓名，3按手机号码。请选择: ";
                k = getche();
                switch (k) {
                    case '1':
                        link.Sort(int(0));                    // 第一个参数传递的数值不重要，重要的是数据类型
                        cout << "\n按序号（升序）排序结果\n" << link << endl;
                        link.Sort(int(0), false);
                        cout << "按序号（降序）排序结果\n" << link << endl;
                        break;
                    case '2':
                        link.Sort(string(""));
                        cout << "\n按姓名（升序）排序结果\n" << link << endl;
                        link.Sort(string(""), false);
                        cout << "按姓名（降序）排序结果\n" << link << endl;
                        break;
                    case '3':
                        link.Sort((long long) (0));
                        cout << "\n按手机号码（升序）排序结果\n" << link << endl;
                        link.Sort((long long) (0), false);
                        cout << "按手机号码（降序）排序结果\n" << link << endl;
                        break;
                }
                break;
            case '7':
            case 'w':
            case 'W':
                n = link.Save(filename);
                cout << "将 " << n << " 个结点的数据写入 "
                     << filename << " 文件。" << endl;
                break;
            case '8':
            case 'r':
            case 'R':
                cout << "读取数据文件。是否先释放已有的所有结点(y/[N])? ";
                yn = getche();
                if (yn == 'y' || yn == 'Y')
                    link.FreeList();
                n = link.Load(filename);
                cout << "从 " << filename << " 文件中读取 "
                     << n << " 个数据。现有 "
                     << link.NumNodes() << " 个结点" << endl;
                break;
            case '9':
            case 'f':
            case 'F':
                cout << "释放所有结点。是否继续(y/[N])? ";
                yn = getche();
                if (yn == 'y' || yn == 'Y')                // 默认 No
                    link.FreeList();
                break;
        }
    }
    if (link.NumNodes()) {
        cout << "\n即将返回主函数，链表数据是否存盘([Y]/n)? ";
        yn = getche();
        if (yn != 'n' && yn != 'N')                            // 默认 Yes
        {
            filename[Pos('.', filename)] = '\0';        // 去掉文件扩展名.txt
            strcat(filename, "(1).txt");                // 拼接成新的文件名
            n = link.Save(filename);
            cout << "\n已将 " << n << " 个结点的数据存入 " << filename << " 文件。" << endl;
        }
    }
    cout << "\n自动调用析构函数释放所有结点，返回主函数。\n" << endl;
}
