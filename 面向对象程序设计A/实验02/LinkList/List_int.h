// List_int.h		单向链表结点数据组织形式描述
#ifndef LIST_INT_H
#define LIST_INT_H

#include <iostream>

using namespace std;

struct Node {
    int data;            // 数据域(虽然这里仅有一个数据，但还是用数据datum的复数形式)
    Node *next;            // 指针域
};

// 以下为4个函数的函数原型（其定义已完成，见List_int.cpp文件）
ostream &operator<<(ostream &out, const Node *head);

Node *Locate(Node *head, int x, int &num, bool newsearch = false);    // 返回找到的结点地址，"返回"该结点的序号num

int Save(const char *filename, const Node *head);

int Load(const char *filename, Node *&head);

// 请在此补充6个函数（Create，NumNodes，ShowList，Insert，Append，FreeList）的函数原型声明

// 1.根据连续存放的数据域数组创建链表
void Create(Node *&head, int n, int *arr = nullptr);

//2. 计算并返回链表的结点个数
int NumNodes(const Node *head);

//3. 输出链表各结点的数据域数据值，要求用 head -> 数据 -> 数据 -> NULL的形式。
int ShowList(const Node *head, ostream &out = cout);

//4. 插入一个新结点至链表首结点前，成为新的链首结点
Node *Insert(Node *&head, int data);

//5. 追加一个新结点至链表尾结点后，成为新的尾结点
Node *Append(Node *&head, int data);

//6. 释放链表中的所有结点
void FreeList(Node *&head);

#endif




