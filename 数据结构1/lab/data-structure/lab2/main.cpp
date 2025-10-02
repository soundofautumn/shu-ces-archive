//
// Created by 邱姜铭 on 2023/12/1.
//
#include <iostream>
#include "Point2D.h"
#include "SeqStack.h"

using namespace std;

int main() {
    SeqStack<Point2D> stack(2);
    Point2D p1(1, 2), p2(3, 4), p3(5, 6);
    stack.Push(p1);
    stack.Push(p2);
    stack.Push(p3);
    cout << "length:"
         << stack.GetLength() << endl;
    cout << "stack is empty:"
         << stack.IsEmpty() << endl;
    cout << "stack: " << endl;
    stack.Traverse([](const Point2D &point2D) {
        cout << point2D << endl;
    });
    Point2D p4;
    stack.Pop(p4);
    cout << "pop: "
         << p4 << endl;
    cout << "stack: " << endl;
    stack.Traverse([](const Point2D &point2D) {
        cout << point2D << endl;
    });
    return 0;
}
