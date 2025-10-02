//
// Created by 邱姜铭 on 2024/1/15.
//

#ifndef DATA_STRUCTURE_LINKSTACK_H
#define DATA_STRUCTURE_LINKSTACK_H

#include "Assistance.h"

template<class ElemType>
class LinkStack {
private:
    struct Node {
        ElemType data;
        Node *next;

        explicit Node(const ElemType &e, Node *nextPtr = nullptr) {
            data = e;
            next = nextPtr;
        }
    };

    Node *top;

public:
    LinkStack();

    virtual ~LinkStack();

    int GetLength() const;

    bool IsEmpty() const;

    void Clear();

    void Traverse(void (*Visit)(const ElemType &)) const;

    Status Push(const ElemType &e);

    Status Top(ElemType &e) const;

    Status Pop(ElemType &e);

};

template<class ElemType>
LinkStack<ElemType>::LinkStack() {
    top = nullptr;
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack() {
    Clear();
}

template<class ElemType>
int LinkStack<ElemType>::GetLength() const {
    int count = 0;
    for (Node *p = top; p != nullptr; p = p->next) {
        count++;
    }
    return count;
}

template<class ElemType>
bool LinkStack<ElemType>::IsEmpty() const {
    return top == nullptr;
}

template<class ElemType>
void LinkStack<ElemType>::Clear() {
    Node *p = top;
    while (p != nullptr) {
        top = top->next;
        delete p;
        p = top;
    }
}

template<class ElemType>
void LinkStack<ElemType>::Traverse(void (*Visit)(const ElemType &)) const {
    for (Node *p = top; p != nullptr; p = p->next) {
        (*Visit)(p->data);
    }
}

template<class ElemType>
Status LinkStack<ElemType>::Push(const ElemType &e) {
    top = new Node(e, top);
    return SUCCESS;
}

template<class ElemType>
Status LinkStack<ElemType>::Top(ElemType &e) const {
    if (IsEmpty()) {
        return UNDER_FLOW;
    }
    e = top->data;
    return SUCCESS;
}

template<class ElemType>
Status LinkStack<ElemType>::Pop(ElemType &e) {
    if (IsEmpty()) {
        return UNDER_FLOW;
    }
    e = top->data;
    Node *p = top;
    top = top->next;
    delete p;
    return SUCCESS;
}


#endif //DATA_STRUCTURE_LINKSTACK_H
