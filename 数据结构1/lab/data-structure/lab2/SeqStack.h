//
// Created by 邱姜铭 on 2023/12/1.
//

#ifndef DATA_STRUCTURE_SEQSTACK_H
#define DATA_STRUCTURE_SEQSTACK_H

#define DEFAULT_SIZE 100

enum Status {
    SUCCESS, OVER_FLOW, RANGE_ERROR, NOT_PRESENT, ENTRY_FOUND, UNDER_FLOW
};

template<class ElemType>
class SeqStack {
private:
    void StackFull();

protected:
    int top; // 栈顶指针
    int maxSize; // 栈最大容量
    ElemType *elems;// 元素存储空间
public:
    explicit SeqStack(int size = DEFAULT_SIZE);

    virtual ~SeqStack();

    int GetLength() const;

    bool IsEmpty() const;

    void Clear();

    Status Push(ElemType e);

    Status Top(ElemType &e) const;

    Status Pop(ElemType &e);

    void Traverse(void(*Visit)(const ElemType &)) const;
};

template<class ElemType>
SeqStack<ElemType>::SeqStack(int size)
// 操作结果：构造一个最大容量为size的空栈
{
    maxSize = size;
    elems = new ElemType[maxSize];
    top = -1;
}

template<class ElemType>
SeqStack<ElemType>::~SeqStack()
// 操作结果：销毁栈
{
    delete[]elems;
}

template<class ElemType>
int SeqStack<ElemType>::GetLength() const
// 操作结果：返回栈中元素个数
{
    return top + 1;
}

template<class ElemType>
bool SeqStack<ElemType>::IsEmpty() const
// 操作结果：如栈为空，则返回true，否则返回false
{
    return top == -1;
}

template<class ElemType>
void SeqStack<ElemType>::Clear() {
    top = -1;
}

template<class ElemType>
Status SeqStack<ElemType>::Push(const ElemType e) {
    if (top == maxSize - 1)
        StackFull(); // 栈满,追加存储空间
    elems[++top] = e; // 将元素e追加到栈顶
    return SUCCESS; // 操作成功
}

template<class ElemType>
Status SeqStack<ElemType>::Top(ElemType &e) const {
    if (IsEmpty()) // 栈空
        return UNDER_FLOW;
    else {
        e = elems[top]; // 用e返回栈顶元素
        return SUCCESS; // 栈非空,操作成功
    }
}

template<class ElemType>
Status SeqStack<ElemType>::Pop(ElemType &e) {
    if (IsEmpty()) // 栈空
        return UNDER_FLOW;
    else {
        e = elems[top--]; // 用e返回栈顶元素
        return SUCCESS; // 操作成功
    }
}

template<class ElemType>
void SeqStack<ElemType>::Traverse(void(*Visit)(const ElemType &)) const {
    for (int i = top; i >= 0; i--)
        (*Visit)(elems[i]);
}

template<class ElemType>
void SeqStack<ElemType>::StackFull() {
    auto *tmp = new ElemType[maxSize * 2];
    for (int i = 0; i < maxSize; ++i) {
        tmp[i] = elems[i];
    }
    delete[]elems;
    elems = tmp;
    maxSize *= 2;
}


#endif //DATA_STRUCTURE_SEQSTACK_H
