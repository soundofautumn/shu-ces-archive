//
// Created by 邱姜铭 on 2023/12/1.
//

#ifndef DATA_STRUCTURE_LINKQUEUE_H
#define DATA_STRUCTURE_LINKQUEUE_H

enum Status {
    SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,
};


template<class ElemType>
class LinkQueue {
protected:
    template<class T>
    struct Node {
        T data;
        Node *next;
    };
    Node<ElemType> *rear; // 队尾指针
public:
    LinkQueue();

    virtual ~LinkQueue();

    int GetLength() const;

    bool IsEmpty() const;

    void Clear();

    Status DelQueue(ElemType &e);

    Status GetHead(ElemType &e) const;

    Status EnQueue(ElemType e);

    void Traverse(void (*visit)(const ElemType &)) const;
};

template<class ElemType>
LinkQueue<ElemType>::LinkQueue() {
    rear = nullptr;
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue() {
    Clear();
}

template<class ElemType>
int LinkQueue<ElemType>::GetLength() const {
    if (IsEmpty()) {
        return 0;
    }
    int length = 1;
    Node<ElemType> *p = rear->next;
    while (p != rear) {
        length++;
        p = p->next;
    }
    return length;
}

template<class ElemType>
bool LinkQueue<ElemType>::IsEmpty() const {
    return rear == nullptr;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear() {
    if(IsEmpty()){
        return;
    }
    Node<ElemType> *p = rear->next;
    while (p != rear) {
        Node<ElemType> *q = p;
        p = p->next;
        delete q;
    }
    delete rear;
    rear = nullptr;
}

template<class ElemType>
Status LinkQueue<ElemType>::EnQueue(const ElemType e) {
    auto *p = new Node<ElemType>;
    p->data = e;
    if (IsEmpty()) {
        rear = p;
        rear->next = rear;
    } else {
        p->next = rear->next;
        rear->next = p;
        rear = p;
    }
    return SUCCESS;
}

template<class ElemType>
Status LinkQueue<ElemType>::GetHead(ElemType &e) const {
    if (IsEmpty()) {
        return UNDER_FLOW;
    }
    e = rear->next->data;
    return SUCCESS;
}

template<class ElemType>
Status LinkQueue<ElemType>::DelQueue(ElemType &e) {
    if (IsEmpty()) {
        return UNDER_FLOW;
    }
    Node<ElemType> *p = rear->next;
    e = p->data;
    if (p == rear) {
        rear = nullptr;
    } else {
        rear->next = p->next;
    }
    delete p;
    return SUCCESS;
}

template<class ElemType>
void LinkQueue<ElemType>::Traverse(void (*Visit)(const ElemType &)) const {
    if (IsEmpty()) {
        return;
    }
    Node<ElemType> *p = rear->next;
    while (p != rear) {
        Visit(p->data);
        p = p->next;
    }
    Visit(p->data);
}

#endif //DATA_STRUCTURE_LINKQUEUE_H
