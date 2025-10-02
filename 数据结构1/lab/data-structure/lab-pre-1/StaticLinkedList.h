//
// Created by 邱姜铭 on 2023/11/29.
//

#ifndef DATA_STRUCTURE_STATICLINKEDLIST_H
#define DATA_STRUCTURE_STATICLINKEDLIST_H

#include <stdexcept>

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE 100
#endif

template<typename T>
class StaticLinkedList {
    typedef int size_type;
    typedef T value_type;

    typedef void (*print_ptr)(const value_type &);

protected:
    struct Node {
        value_type data;
        size_type next;
    };

    // 数组
    Node *arr;
    // 数组长度
    const size_type arr_size;
    // 链表长度
    size_type size;
    // 头指针
    size_type &head = arr[0].next;
    // 空闲链表头指针
    size_type avail;

public:
    explicit StaticLinkedList(size_type max_size = DEFAULT_SIZE);

    StaticLinkedList(const StaticLinkedList &list);

    StaticLinkedList &operator=(const StaticLinkedList &list);

    ~StaticLinkedList();

    bool insert(size_type pos, const value_type &value);

    inline bool insert(const value_type &value);

    bool remove(size_type pos);

    bool set(size_type pos, const value_type &value);

    value_type get(size_type pos) const;

    size_type find(const value_type &value) const;

    size_type getSize() const;

    bool empty() const;

    bool full() const;

    void clear();

    void print(print_ptr printPtr) const;

};

template<typename T>
StaticLinkedList<T>::StaticLinkedList(StaticLinkedList::size_type max_size)
        :arr(new Node[max_size + 1]), avail(1), arr_size(max_size), size(0) {
    // head 指向 -1 即空链表
    this->arr[0].next = -1;
    // 初始化空闲链表
    for (size_type i = 1; i < this->arr_size; ++i) {
        this->arr[i].next = i + 1;
    }
    // 最后一个节点的next指向-1 即空闲链表的最后一个节点
    this->arr[this->arr_size].next = -1;
}

template<typename T>
StaticLinkedList<T>::StaticLinkedList(const StaticLinkedList &list)
        :arr(new Node[list.arr_size + 1]), avail(list.avail), arr_size(list.arr_size), size(list.size) {
    // 复制数据 范围是 [0, arr_size]
    for (size_type i = 0; i <= this->arr_size; ++i) {
        this->arr[i].data = list.arr[i].data;
        this->arr[i].next = list.arr[i].next;
    }
}

template<typename T>
StaticLinkedList<T> &StaticLinkedList<T>::operator=(const StaticLinkedList &list) {
    if (this == &list) {
        return *this;
    }
    delete[] this->arr;
    this->arr = new Node[list.arr_size + 1];
    this->avail = list.avail;
    this->arr_size = list.arr_size;
    this->size = list.size;
    for (size_type i = 0; i <= this->arr_size; ++i) {
        this->arr[i].data = list.arr[i].data;
        this->arr[i].next = list.arr[i].next;
    }
    return *this;
}

template<typename T>
StaticLinkedList<T>::~StaticLinkedList() {
    delete[] this->arr;
}

template<typename T>
bool StaticLinkedList<T>::insert(size_type pos, const value_type &value) {
    // pos 从 0 开始 因为是插入 所以pos的范围是 [0, size)
    // 如果是空链表 pos 只能是 0
    if (!(pos == 0 && this->empty()) && (pos < 0 || pos >= this->size)) {
        return false;
    }
    if (this->full()) {
        return false;
    }
    // 先找到插入位置的前一个位置
    size_type i = 0;
    for (size_type j = 0; j < pos; ++j) {
        i = this->arr[i].next;
    }
    // 从空闲链表中取出一个节点
    const size_type k = this->avail;
    // 更新空闲链表
    this->avail = this->arr[this->avail].next;
    // 为节点赋值
    this->arr[k].data = value;
    this->arr[k].next = this->arr[i].next;
    // 更新前一个节点的next
    this->arr[i].next = k;
    this->size++;
    return true;
}

template<typename T>
inline bool StaticLinkedList<T>::insert(const value_type &value) {
    // 头插法
    return this->insert(0, value);
}

template<typename T>
bool StaticLinkedList<T>::remove(size_type pos) {
    // pos 从 0 开始 因为是删除 所以pos的范围是 [0, size)
    if (pos < 0 || pos >= this->size) {
        return false;
    }
    // 先找到删除位置的前一个位置
    size_type i = 0;
    for (size_type j = 0; j < pos; ++j) {
        i = this->arr[i].next;
    }
    // 要删除的节点
    const size_type k = this->arr[i].next;
    // 更新前一个节点的next
    this->arr[i].next = this->arr[k].next;
    // 将删除的节点加入空闲链表
    this->arr[k].next = this->avail;
    this->avail = k;
    this->size--;
    return true;
}

template<typename T>
bool StaticLinkedList<T>::set(size_type pos, const value_type &value) {
    // pos 从 0 开始 因为是修改 所以pos的范围是 [0, size)
    if (pos < 0 || pos >= this->size) {
        return false;
    }
    size_type i = this->head;
    for (size_type j = 0; j < pos; ++j) {
        i = this->arr[i].next;
    }
    this->arr[i].data = value;
    return true;
}

template<typename T>
typename StaticLinkedList<T>::value_type StaticLinkedList<T>::get(size_type pos) const {
    // pos 从 0 开始 因为是获取 所以pos的范围是 [0, size)
    if (pos < 0 || pos >= this->size) {
        throw std::out_of_range("out of range");
    }
    size_type i = this->head;
    for (size_type j = 0; j < pos; ++j) {
        i = this->arr[i].next;
    }
    return this->arr[i].data;
}

template<typename T>
typename StaticLinkedList<T>::size_type StaticLinkedList<T>::find(const value_type &value) const {
    // 从头开始遍历
    size_type i = this->head;
    size_type j = 0;
    while (i != -1) {
        if (this->arr[i].data == value) {
            return j;
        }
        i = this->arr[i].next;
        j++;
    }
    // 如果没有找到 返回-1
    return -1;
}

template<typename T>
typename StaticLinkedList<T>::size_type StaticLinkedList<T>::getSize() const {
    return this->size;
}

template<typename T>
bool StaticLinkedList<T>::empty() const {
    return this->head == -1;
}

template<typename T>
bool StaticLinkedList<T>::full() const {
    return this->avail == -1;
}

template<typename T>
void StaticLinkedList<T>::clear() {
    // 只要重置指针域 数据域不需要重置
    this->head = -1;
    this->avail = 1;
    for (size_type i = 1; i < this->size; ++i) {
        this->arr[i].next = i + 1;
    }
    this->arr[this->size].next = -1;
    this->size = 0;
}

template<typename T>
void StaticLinkedList<T>::print(print_ptr printPtr) const {
    size_type i = this->head;
    while (i != -1) {
        printPtr(this->arr[i].data);
        i = this->arr[i].next;
    }
}

#endif //DATA_STRUCTURE_STATICLINKEDLIST_H
