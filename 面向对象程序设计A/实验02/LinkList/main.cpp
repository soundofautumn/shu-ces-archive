// Main.cpp					这是测试程序，无须修改
#define _CRT_SECURE_NO_WARNINGS

#include "List_int.h"
#include <cstring>

#ifdef _MSC_VER
#include <conio.h>
#else
#define _getch() cin.get()
#define _getche() cin.get()
#endif

int Pos(char ch, const char *str)            // 返回指定字符ch在字符串str中的下标。不存在时返回-1
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
        if (ch == str[i])
            return i;
    return -1;
}

int Choice(const char *prompt, const char *options = "")    // 输出提示信息prompt，输入选择的字符并返回。
{
    int key;
    cout << prompt << "{";
    for (int i = 0; options[i] != '\0'; i++) {
        if (' ' < (options[i] & 0x7f) && (options[i] & 0x7f) < 127)    // 选项options中的可打印字符
            cout << options[i] << ' ';
        else                                                        // 选项options中的部分控制字符
        {
            switch (options[i]) {
                case '\t':
                    cout << "[Tab] ";
                    break;                    // 选项中的Tab字符'\t'（即ASCII编码9）
                case '\x1b':
                    cout << "[Esc] ";
                    break;                    // 选项中的Esc字符'\x1b'（即ASCII编码27）
                case ' ':
                    cout << "[Space] ";
                    break;                    // 选项中的空格字符' '（即ASCII编码32）
            }
        }
    }
    cout << "\b}: ";                    // '\b'退格。先退一格，再输出右花括号
    do {
        key = _getch();
    } while (options[0] != '\0' && Pos(key, options) < 0); // 若options为空长度为0的字符串，则输入无限制；否则输入项应该在optins中。
    cout << endl;
    return key;
}

void Init(Node *&head)                    // 测试Create。利用连续存放的数组元素创建链表
{
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 2, 5, 2, 5, 8};
    int n = sizeof(array) / sizeof(*array);
    Create(head, n, array);
}

void Find(Node *head, int x)            // 测试Locate。请特别注意"查找/继续查找"
{
    Node *p;
    int n = 0, num;
    p = Locate(head, x, num, true);
    while (p != nullptr) {
        cout << "找到第 " << num << " 结点(编号从0开始)：\t" << p->data << endl;
        n++;
        p = Locate(head, x, num);
    }
    cout << "\t共找到 " << n << " 个结点，满足条件。" << endl;
}

int main() {
    Node *head = nullptr;        // 创建一条完整的链表
    char filename[80] = "data_int.txt";
    int x;                    // 与数据域类型相同的变量
    int n, key, yn;

    Init(head);                // 测试Create
    while (true) {
        cout << "\n========== MENU ==========" << endl;
        cout << "  1 ---- 输 出 链 表 (P)" << endl;
        cout << "  2 ---- 插 入 结 点 (I)" << endl;
        cout << "  3 ---- 追 加 结 点 (A)" << endl;
        cout << "  4 ---- 查 询 结 点 (S)" << endl;
        cout << "  5 ---- 数据写入文件(W)" << endl;
        cout << "  6 ---- 读取数据文件(R)" << endl;
        cout << "  7 ---- 释放所有结点(F)" << endl;
        cout << "  0 ---- 退      出(ESC)" << endl;
        cout << "==========================" << endl;
        key = Choice("请选择", "01234567\x1bpPiIaAsSwWrRfF");
        cout << "\n\n";
        if (key == 27 || key == '0')        // '\x1b'等于27，指ESC键
            break;
        switch (key) {
            case '1':
            case 'p':
            case 'P':
                cout << "第一种格式输出" << endl;
                ShowList(head);
                cout << "\n第二种格式输出" << endl;
                cout << head << endl;
                break;
            case '2':
            case 'i':
            case 'I':
                cout << "插入一个结点到链表首结点前。请输入数据域数据(int): ";
                cin >> x;
                Insert(head, x);
                break;
            case '3':
            case 'a':
            case 'A':
                cout << "追加一个结点(至尾结点后)。请输入数据域数据(int): ";
                cin >> x;
                Append(head, x);
                break;
            case '4':
            case 's':
            case 'S':
                cout << "根据数据域数据查询。请输入待查询的数据(int): ";
                cin >> x;
                Find(head, x);
                break;
            case '5':
            case 'w':
            case 'W':
                n = Save(filename, head);
                cout << "将 " << n << " 个结点的数据写入 "
                     << filename << " 文件。" << endl;
                break;
            case '6':
            case 'r':
            case 'R':
                cout << "读取数据文件。是否先释放已有的所有结点(y/[N])? ";
                yn = _getche();
                if (yn == 'y' || yn == 'Y')
                    FreeList(head);
                n = Load(filename, head);
                cout << "从 " << filename << " 文件中读取 "
                     << n << " 个数据。" << endl;
                break;
            case '7':
            case 'f':
            case 'F':
                cout << "释放所有结点。是否继续(y/[N])? ";
                yn = _getche();
                if (yn == 'y' || yn == 'Y')                // 默认 No
                    FreeList(head);
                break;
        }
    }
    if (head != nullptr) {
        cout << "\n即将退出程序，链表数据是否存盘([Y]/n)? ";
        yn = _getche();
        if (yn != 'n' && yn != 'N')                            // 默认 Yes
        {
            filename[Pos('.', filename)] = '\0';        // 去掉文件扩展名.txt
            strcat(filename, "(1).txt");                // 拼接成新的文件名
            n = Save(filename, head);
            cout << "\n已将 " << n << " 个结点的数据存入 " << filename << " 文件。" << endl;
        }
    }
    cout << "\n释放所有结点，返回操作系统。" << endl;
    FreeList(head);
    return 0;
}
