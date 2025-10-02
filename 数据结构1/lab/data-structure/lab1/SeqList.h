//
// Created by 邱姜铭 on 2023/11/28.
//

#ifndef DATA_STRUCTURE_SEQLIST_H
#define DATA_STRUCTURE_SEQLIST_H

#include <iostream>
#include <cassert>

#define DEFAULT_SIZE 100

#ifndef LIST_STATUS
#define LIST_STATUS
enum Status {
    SUCCESS, OVER_FLOW, RANGE_ERROR, NOT_PRESENT, ENTRY_FOUND
};
#endif

template<class ElemType>
class SeqList {
protected:
    int length;
    int maxLength;
    ElemType *elems;
public:
    explicit SeqList(int size = DEFAULT_SIZE);

    SeqList(ElemType v[], int n, int size = DEFAULT_SIZE);

    SeqList(const SeqList<ElemType> &sa);

    virtual ~SeqList();

    int GetLength() const;

    bool IsEmpty() const;

    void Clear();

    void Traverse(void (*Visit)(const ElemType &)) const;

    int LocateElem(const ElemType &e) const;

    Status GetElem(int i, ElemType &e) const;

    Status SetElem(int i, const ElemType &e);

    Status DeleteElem(int i, ElemType &e);

    Status InsertElem(int i, const ElemType &e);

    Status InsertElem(const ElemType &e);

    Status DelSameItem(const ElemType &e);

    Status Reverse();

    SeqList<ElemType> &operator=(const SeqList<ElemType> &sa);
};

template<class ElemType>
SeqList<ElemType>::SeqList(int size) {
    elems = new ElemType[size];
    assert(elems);
    maxLength = size;
    length = 0;
}

template<class ElemType>
SeqList<ElemType>::SeqList(ElemType v[], int n, int size) {
    elems = new ElemType[size];
    assert(elems);
    maxLength = size;
    length = n;
    for (int i = 0; i < length; i++)
        elems[i] = v[i];
}

template<class ElemType>
SeqList<ElemType>::~SeqList() {
    delete[]elems;
}

template<class ElemType>
int SeqList<ElemType>::GetLength() const {
    return length;
}

template<class ElemType>
SeqList<ElemType>::SeqList(const SeqList<ElemType> &sa) {
    elems = new ElemType[sa.maxLength];
    assert(elems);
    maxLength = sa.maxLength;
    length = sa.length;
    for (int i = 0; i < length; i++)
        elems[i] = sa.elems[i];
}

template<class ElemType>
SeqList<ElemType> &SeqList<ElemType>::operator=(const SeqList<ElemType> &sa) {
    if (&sa != this) {
        delete[]elems;
        elems = new ElemType[sa.maxLength];
        assert(elems);
        maxLength = sa.maxLength;
        length = sa.length;
        for (int i = 0; i < length; i++)
            elems[i] = sa.elems[i];
    }
    return *this;
}

template<class ElemType>
void SeqList<ElemType>::Clear() {
    length = 0;
}

template<class ElemType>
void SeqList<ElemType>::Traverse(void (*visit)(const ElemType &)) const {
    for (int i = 1; i <= length; i++)
        (*visit)(elems[i - 1]);
}

template<class ElemType>
int SeqList<ElemType>::LocateElem(const ElemType &e) const {
    int i = 0;
    while (i < length && elems[i] != e) i++;
    return i < length ? i + 1 : 0;
}

template<class ElemType>
Status SeqList<ElemType>::GetElem(int i, ElemType &e) const {
    if (i < 1 || i > length) return NOT_PRESENT;
    else {
        e = elems[i - 1];
        return ENTRY_FOUND;
    }
}

template<class ElemType>
Status SeqList<ElemType>::SetElem(int i, const ElemType &e) {
    if (i < 1 || i > length) return RANGE_ERROR;
    else {
        elems[i - 1] = e;
        return SUCCESS;
    }
}

template<class ElemType>
Status SeqList<ElemType>::DeleteElem(int i, ElemType &e) {
    if (i < 1 || i > length)
        return RANGE_ERROR;
    else {
        e = elems[i - 1];
        for (int j = i; j < length; j++)
            elems[j - 1] = elems[j];
        length--;
        return SUCCESS;
    }
}

template<class ElemType>
Status SeqList<ElemType>::InsertElem(int i, const ElemType &e) {
    if (length == maxLength) return OVER_FLOW;
    else if (i < 1 || i > length + 1) return RANGE_ERROR;
    else {
        for (int j = length; j >= i; j--)
            elems[j] = elems[j - 1];
        elems[i - 1] = e;
        length++;
        return SUCCESS;
    }
}

template<class ElemType>
Status SeqList<ElemType>::InsertElem(const ElemType &e) {
    if (length == maxLength)
        return OVER_FLOW;
    else {
        elems[length] = e;
        length++;
        return SUCCESS;
    }
}

template<class ElemType>
bool SeqList<ElemType>::IsEmpty() const {
    return length == 0;
}

template<class ElemType>
Status SeqList<ElemType>::DelSameItem(const ElemType &e) {
    int i = 0, j = 0;
    while (j < length) {
        if (elems[j] != e) {
            elems[i] = elems[j];
            i++;
        }
        j++;
    }
    length = i;
    return SUCCESS;
}

template<class ElemType>
Status SeqList<ElemType>::Reverse() {
    int i = 0, j = length - 1;
    while (i < j) {
        ElemType temp = elems[i];
        elems[i] = elems[j];
        elems[j] = temp;
        i++;
        j--;
    }
    return SUCCESS;
}

#endif //DATA_STRUCTURE_SEQLIST_H
