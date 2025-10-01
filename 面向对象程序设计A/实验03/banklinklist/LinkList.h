//
// Created by 邱姜铭 on 2023/10/7.
//

#ifndef BANKLINKLIST_LINKLIST_H
#define BANKLINKLIST_LINKLIST_H

#include <iostream>

template<class T>
class LinkList {


private:
    typedef bool (*cmp_ptr)(const T &, const T &);

    typedef void (*print_ptr)(const T &, std::ostream &);

    static bool default_cmp(const T &a, const T &b) {
        return a == b;
    }

    struct node {
        T *data;
        node *next = nullptr;
    };
    node *head = nullptr;
public:
    LinkList();

    ~LinkList();

    void insert_node(T *data);

    void delete_node(T *data, cmp_ptr compare = default_cmp) noexcept(false);

    bool contain(T *data, cmp_ptr compare = default_cmp);

    T *&find(T *data, cmp_ptr compare = default_cmp) noexcept(false);

    void print_all(print_ptr print = [](const T &data) { std::cout << data << std::endl; },
                   std::ostream &out = std::cout);


};

template<class T>
LinkList<T>::LinkList() {
    head = nullptr;
}

template<class T>
LinkList<T>::~LinkList() {
    node *p = head;
    while (p != nullptr) {
        node *next = p->next;
        delete p;
        p = next;
    }
}

template<class T>
void LinkList<T>::insert_node(T *data) {
    node *old = head;
    head = new node();
    head->next = old;
    head->data = data;
}

template<class T>
void LinkList<T>::delete_node(T *data, cmp_ptr compare) {
    if (head == nullptr) {
        throw std::out_of_range("没有找到对应数据的节点，请检查要删除的节点是否存在\n");
    }
    node *p = head;
    if (compare(*p->data, *data)) {
        head = p->next;
        delete p;
        return;
    }
    if (p->next == nullptr) {
        throw std::out_of_range("没有找到对应数据的节点，请检查要删除的节点是否存在\n");
    }
    while (!compare(*p->next->data, *data)) {
        if (p->next->next == nullptr) {
            throw std::out_of_range("没有找到对应数据的节点，请检查要删除的节点是否存在\n");
        }
        p = p->next;
    }
    node *next = p->next->next;
    delete p->next;
    p->next = next;
}

template<class T>
void LinkList<T>::print_all(print_ptr print, std::ostream &out) {
    node *p = head;
    while (p != nullptr) {
        print(*p->data, out);
        p = p->next;
    }
}

template<class T>
bool LinkList<T>::contain(T *data, cmp_ptr compare) {
    if (head == nullptr) {
        return false;
    }
    node *p = head;
    while (!compare(*p->data, *data)) {
        if (p->next == nullptr) {
            return false;
        }
        p = p->next;
    }
    return true;
}

template<class T>
T *&LinkList<T>::find(T *data, cmp_ptr compare) {
    if (head == nullptr) {
        throw std::out_of_range("没有找到对应数据的节点，请检查要删除的节点是否存在\n");
    }
    node *p = head;
    while (!compare(*p->data, *data)) {
        if (p->next == nullptr) {
            throw std::out_of_range("没有找到对应数据的节点，请检查要删除的节点是否存在\n");
        }
        p = p->next;
    }
    return p->data;
}


#endif //BANKLINKLIST_LINKLIST_H
