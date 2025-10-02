//
// Created by 邱姜铭 on 2023/11/29.
//

#ifndef DATA_STRUCTURE_DBLLINKLIST_H
#define DATA_STRUCTURE_DBLLINKLIST_H

#include "DblNode.h"

#ifndef LIST_STATUS
#define LIST_STATUS
enum Status {
    SUCCESS, OVER_FLOW, RANGE_ERROR, NOT_PRESENT, ENTRY_FOUND
};
#endif

template<class ElemType>
class DblLinkList {
protected:
    DblNode<ElemType> *head;
    int length;
public:
    DblLinkList();

    DblLinkList(ElemType v[], int n);

    virtual ~DblLinkList();

    int GetLength() const;

    bool IsEmpty() const;

    void Clear();

    void Traverse(void (*Visit)(const ElemType &)) const;

    int LocateElem(const ElemType &e);

    Status GetElem(int i, ElemType &e) const;

    Status SetElem(int i, const ElemType &e);

    Status DeleteElem(int i, ElemType &e);

    Status InsertElem(int i, const ElemType &e);

    Status InsertElem(const ElemType &e);

    DblLinkList(const DblLinkList<ElemType> &la);

    DblLinkList<ElemType> &operator=(const DblLinkList<ElemType> &la);
};

template<class ElemType>
DblLinkList<ElemType>::DblLinkList() {
    head = nullptr;
    length = 0;
}

template<class ElemType>
DblLinkList<ElemType>::DblLinkList(ElemType v[], int n) {
    head = new DblNode<ElemType>;
    head->data = v[0];
    DblNode<ElemType> *p = head;
    for (int i = 1; i < n; i++) {
        p->next = new DblNode<ElemType>(v[i], p);
        p = p->next;
    }
    length = n;
    head->prior = p;
    p->next = head;
}

template<class ElemType>
DblLinkList<ElemType>::~DblLinkList() {
    Clear();
    delete head;
}

template<class ElemType>
int DblLinkList<ElemType>::GetLength() const {
    return length;
}

template<class ElemType>
bool DblLinkList<ElemType>::IsEmpty() const {
    return length == 0;
}

template<class ElemType>
void DblLinkList<ElemType>::Clear() {
    ElemType tmpElem;
    while (length > 0)
        DeleteElem(1, tmpElem);
}

template<class ElemType>
void DblLinkList<ElemType>::Traverse(void (*Visit)(const ElemType &)) const {
    DblNode<ElemType> *p;
    (*Visit)(head->data);
    for (p = head->next; p != head; p = p->next)
        (*Visit)(p->data);
}

template<class ElemType>
int DblLinkList<ElemType>::LocateElem(const ElemType &e) {
    if (head->data == e) {
        return 1;
    }
    DblNode<ElemType> *p = head->next;
    int count = 2;
    while (p != head && p->data != e) {
        count++;
        p = p->next;
    }
    if (p != head) return count;
    else return 0;
}

template<class ElemType>
Status DblLinkList<ElemType>::GetElem(int i, ElemType &e) const {
    DblNode<ElemType> *p = head->next;
    if (i < 1 || i > length) return NOT_PRESENT;
    else if (head->data == e) {
        e = head->data;
        return ENTRY_FOUND;
    } else {
        for (int count = 2; count < i; count++) p = p->next;
        e = p->data;
        return ENTRY_FOUND;
    }
}

template<class ElemType>
Status DblLinkList<ElemType>::SetElem(int i, const ElemType &e) {
    DblNode<ElemType> *p = head->next;
    int count;
    if (i < 1 || i > length) return RANGE_ERROR;
    else if (i == 1) {
        head->data = e;
        return ENTRY_FOUND;
    } else {
        for (count = 2; count < i; count++) p = p->next;
        p->data = e;
        return SUCCESS;
    }
}

template<class ElemType>
Status DblLinkList<ElemType>::DeleteElem(int i, ElemType &e) {
    DblNode<ElemType> *p = head->next;
    int count;
    if (i < 1 || i > length) return RANGE_ERROR;
    else if (i == 1) {
        delete head;
        head = nullptr;
        length = 0;
        return ENTRY_FOUND;
    } else {
        for (count = 2; count < i; count++) p = p->next;
        p->prior->next = p->next;
        p->next->prior = p->prior;
        e = p->data;
        length--;
        delete p;
        return SUCCESS;
    }
}

template<class ElemType>
Status DblLinkList<ElemType>::InsertElem(int i, const ElemType &e) {
    DblNode<ElemType> *p = head->next, *q;
    int count;
    if (i < 1 || i > length + 1) return RANGE_ERROR;
    else if (i == 1) {
        return InsertElem(e);
    } else {
        for (count = 2; count < i; count++) p = p->next;
        q = new DblNode<ElemType>(e, p->prior, p);
        p->prior->next = q;
        p->prior = q;
        length++;
        return SUCCESS;
    }
}

template<class ElemType>
Status DblLinkList<ElemType>::InsertElem(const ElemType &e) {
    if (head == nullptr) {
        head = new DblNode<ElemType>(e);
        head->prior = head;
        head->next = head;
        length++;
        return SUCCESS;
    }
    DblNode<ElemType> *p;
    p = new DblNode<ElemType>(e, head->prior, head);
    head->prior->next = p;
    head->prior = p;
    length++;
    return SUCCESS;
}

template<class ElemType>
DblLinkList<ElemType>::DblLinkList(const DblLinkList<ElemType> &la) {
    DblNode<ElemType> *p, *q;
    head = new DblNode<ElemType>;
    head->data = la.head->data;
    p = head;
    for (q = la.head->next; q != la.head; q = q->next) {
        p->next = new DblNode<ElemType>(q->data, p);
        p = p->next;
    }
    length = la.length;
    head->prior = p;
    p->next = head;
}

template<class ElemType>
DblLinkList<ElemType> &DblLinkList<ElemType>::operator=(const DblLinkList<ElemType> &la) {
    DblNode<ElemType> *p, *q;
    if (&la != this) {
        Clear();
        delete head;
        head = new DblNode<ElemType>;
        head->data = la.head->data;
        p = head;
        for (q = la.head->next; q != la.head; q = q->next) {
            p->next = new DblNode<ElemType>(q->data, p);
            p = p->next;
        }
        length = la.length;
        head->prior = p;
        p->next = head;
    }
    return *this;
}

#endif //DATA_STRUCTURE_DBLLINKLIST_H
