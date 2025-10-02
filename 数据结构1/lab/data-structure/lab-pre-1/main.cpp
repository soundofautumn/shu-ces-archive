//
// Created by 邱姜铭 on 2023/11/29.
//
#include <iostream>
#include "StaticLinkedList.h"

using namespace std;

int main() {
    auto print_int = [](const int &data) {
        cout << data << " ";
    };
    StaticLinkedList<int> list(10);
    //填充测试数据
    for (int i = 1; i < 8; ++i) {
        list.insert(i);
    }

    //链表长度查询
    cout << "the length of the list is " << list.getSize() << endl;
    cout << "the list is: ";
    list.print(print_int);
    cout << endl;

    //任意位置改变数据测试
    cout << "set the first element to 10 result: "
         << list.set(0, 10) << endl;
    cout << "set the third element to 10 result: "
         << list.set(2, 10) << endl;
    cout << "set the tenth element to 10 result: "
         << list.set(9, 10) << endl;
    cout << "the list is: ";
    list.print(print_int);
    cout << endl;

    cout << "============================" << endl;

    //任意位置删除数据测试
    cout << "remove the first element result: "
         << list.remove(0) << endl;
    cout << "remove the third element result: "
         << list.remove(2) << endl;
    cout << "remove the tenth element result: "
         << list.remove(9) << endl;
    cout << "the length of the list is " << list.getSize() << endl;
    cout << "the list is: ";
    list.print(print_int);
    cout << endl;

    cout << "============================" << endl;

    //根据数据查询测试
    cout << "the position of 2 is "
         << list.find(2) << endl;
    cout << "the position of 3 is "
         << list.find(3) << endl;
    cout << "the position of 100 is "
         << list.find(100) << endl;

    //根据下标查询测试
    cout << "the third element is: "
         << list.get(2) << endl;
    try {
        cout << "the tenth element is: "
             << list.get(9) << endl;
    } catch (const out_of_range &e) {
        cout << e.what() << endl;
    }

    cout << "============================" << endl;

    // 任意位置插入测试
    cout << "insert 11 at the second position result: "
         << list.insert(1, 11) << endl;
    cout << "the list is: ";
    list.print(print_int);
    cout << endl;

    cout << "============================" << endl;

    // 头插法测试
    for (int i = 0; i < 10; ++i) {
        cout << "insert " << i
             << " insert result: "
             << list.insert(i) << endl;
    }
    cout << "the list is: ";
    list.print(print_int);
    cout << endl;

    cout << "============================" << endl;

    //检查链表是否已满
    cout << "the list is full: "
         << list.full() << endl;

    //改变任意位置元素测试
    cout << "set the tenth element to 10 result: "
         << list.set(9, 10) << endl;
    cout << "the list is:";
    list.print(print_int);
    cout << endl;

    //清空链表测试
    cout << "clear the list" << endl;
    list.clear();
    cout << "the list is empty: "
         << list.empty() << endl;
    cout << "the list is: ";
    list.print(print_int);
    cout << endl;

    //空链表查询的边界情况测试
    cout << "the position of 1 is: "
         << list.find(1) << endl;

    cout << "============================" << endl;
    cout << "insert 1 at the first position result: "
         << list.insert(0, 1) << endl;
    cout << "the list is: ";
    list.print(print_int);
    cout << endl;

    //删除空链表的边界情况测试
    cout << "delete the first element result: "
         << list.remove(0) << endl;
    cout << "the list is: ";
    list.print(print_int);

}
