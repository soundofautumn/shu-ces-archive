// List_int.cpp	（不带头结点）单向链表处理函数
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "List_int.h"

using namespace std;

// 以下为4个函数的函数的定义，其函数声明（函数原型）见List_int.h文件

/* 提示：这是重载运算符 <<，使之能够对链表（Node *）类型进行输出
1. 运算符 << 是双目运算，即需要两个操作数（例如 cout << a; 中，cout是第一操作数，a的第二操作数）。
2. operator<< 为函数名，两个形式参数依次为第一、第二操作数。
3. 第一个形式参数为引用型参数，类型与std名字空间中的全局对象cout属于同一种数据类型。
   亦即大多数情况下，引用out将绑定cout（大多数情况下out是cout的别名）。
   然而，还不限于cout做实参。即还可以用文件对象做实参，那么就可以直接输出到文件。
4. 第二个形式参数用于传递链表的首地址。
5. 函数的返回类型设计成：引用返回out。即不是值返回，不另外创建输出(设备)对象，而是直接返回第一个参数绑定的输出(设备)对象。
   亦即：如果第一个参数是 cout，那么本函数也返回 cout。这样，可保证运算符 << 实现连续输出
   例如运算表达式：cout << a << ", " << b 实际上是 (((cout << a) << ", ") << b。其中(cout << a)就是cout，
   故可以继续执行(cout << ", ")，结果还是cout，进一步执行 cout << b。结果还是cout。
*/
ostream &operator<<(ostream &out, const Node *head)// 重载输出运算符（<<），使得能够直接用运算符<<输出整条链表
{                                                    // 这是C++不用printf函数处理输出的原因之一
    for (; head != nullptr; head = head->next)
        out << head->data << endl;                    // 输出：每个结点的数据占一行
    return out;
}

/* 思考题
1. 形式参数newsearch的作用是什么？
2. 形式参数 num 有何作用？
3. 为什么要将 p，k，data 设计成静态局部变量？
4. 局部自动指针变量 temp 的作用是什么？
5. 函数的返回值是什么？如何区别是否找到满足条件的结点
6. 若形参newsearch为false，此时形参 x 有无作用？为什么要这样设计？
答：对于一种条件的搜索，不能穿插另外一种条件的继续搜索。因此，此时需要故意废掉x。
*/
Node *Locate(Node *head, int x, int &num, bool newsearch) {
    static Node *p = head;
    static int data = x;            // 与数据域的类型相同
    static int k = 0;                // 整型：计数用
    Node *temp;
    if (newsearch) {
        p = head;
        data = x;
        k = 0;
    }
    for (; p != nullptr && p->data != data; p = p->next, k++)    // 从链表的"当前"结点起继续查找
        ;
    temp = p;
    num = k;
    if (p != nullptr)        // 如果找到，在返回找到的结点地址（temp）之前，p"悄悄"地向前走一步，为继续查找做好准备
    {
        p = p->next;
        k++;
    }
    return temp;
}

/* 提示
1. 用到文件流类及其对象（参见教材第14章第2节 文件I/O流）。
2. 此处打开文件采用默认的文本文件方式。
3. 对于链表结点数据域数据类型(int)，要求能进行 << 和 >> 操作(OK)。
4. 输出到文件的格式要能够使Load函数正确地读取。
*/
int Save(const char *filename, const Node *head) {
    ofstream outfile(filename);            // 打开文件（用于将数据写入其中）
    if (outfile.fail())
        return 0;
    int n = 0;                            // 用于计数的整型变量
#if(1)                                    // 将 #if(1) 改成 #if(0) 皆可
    const Node *p;                        // 如果不是为了n的计数。此处可以直接用 outfile << head; 取代下面的 for 循环
    for (p = head; p != nullptr; p = p->next, n++)    // 遍历链表，将各结点的数据域数据输出到文件中
        outfile << p->data << endl;
#else
    outfile << head;					// 调用 operator<< 函数
    n = NumNodes(head);
#endif
    outfile.close();                    // 关闭文件（将缓冲区中的数据真正写入到文件中）这一点很重要！
    return n;
}

int Load(const char *filename, Node *&head) {
    int n;                            // 用于计数的整型变量
    int x;                            // 与数据域类型相同的变量
    ifstream infile(filename);        // 打开文件（用于读取其中的数据）
    if (infile.fail())
        return 0;
    for (n = 0; infile >> x; n++)        // 从数据文件中读取数据，并形成一条链表
        Append(head, x);
    infile.close();                    // 关闭文件
    return n;
}

// 请在此完成6个函数（Create，NumNodes，ShowList，Insert，Append，FreeList）的定义

// 1.根据连续存放的数据域数组创建链表
void Create(Node *&head, int n, int *arr) {
    if (head != nullptr)
        FreeList(head);
    for (int i = n; i-- > 0;)
        Insert(head, arr[i]);
}

//2. 计算并返回链表的结点个数
int NumNodes(const Node *head) {
    int count = 0;
    for (; head != nullptr; head = head->next)
        count++;
    return count;
}

//3. 输出链表各结点的数据域数据值，要求用 head -> 数据 -> 数据 -> NULL的形式。
int ShowList(const Node *head, ostream &out) {
    int count = 0;
    for (; head != nullptr; head = head->next, count++)
        out << head->data << " -> ";
    out << "NULL";
    return count;
}

//4. 插入一个新结点至链表首结点前，成为新的链首结点
Node *Insert(Node *&head, const int data) {
    Node *old = head;
    head = new Node();
    head->next = old;
    head->data = data;
    return head;
}

//5. 追加一个新结点至链表尾结点后，成为新的尾结点
Node *Append(Node *&head, int data) {
    if (head == nullptr) {
        head = new Node();
        head->next = nullptr;
        head->data = data;
        return head;
    } else {
        Node *p = head;
        for (; p->next != nullptr; p = p->next);
        p->next = new Node();
        p = p->next;
        p->next = nullptr;
        p->data = data;
        return p;
    }
}

//6. 释放链表中的所有结点
void FreeList(Node *&head) {
    while (head != nullptr) {
        Node *next = head->next;
        delete head;
        head = next;
    }
}