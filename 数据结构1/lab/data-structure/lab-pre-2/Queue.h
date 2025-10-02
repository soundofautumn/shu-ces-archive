//
// Created by 邱姜铭 on 2023/12/13.
//

#ifndef DATA_STRUCTURE_QUEUE_H
#define DATA_STRUCTURE_QUEUE_H

#include <iostream>
#include "common_exception.h"

namespace flight {
    template<typename T>
    class Queue {

    private:
        typedef T value_type;
        struct Node {
            value_type data;
            Node *next;
        } *front, *rear;
    public:

        explicit Queue();

        ~Queue();

        void enqueue(value_type &&element);

        value_type &&dequeue();

        value_type peek();

        bool is_empty();

        std::ostream &operator<<(std::ostream &os) const;

        friend std::ostream &operator<<(std::ostream &os, const Queue &queue) {
            return queue.operator<<(os);
        }

        std::istream &operator>>(std::istream &is);

        friend std::istream &operator>>(std::istream &is, Queue &queue) {
            return queue.operator>>(is);
        }

        class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
        private:
            Node *p;
        public:
            explicit iterator(Node *p) : p(p) {}

            value_type &operator*() const {
                return p->data;
            }

            value_type *operator->() const {
                return &p->data;
            }

            iterator &operator++() {
                p = p->next;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp = *this;
                ++*this;
                return tmp;
            }

            bool operator==(const iterator &rhs) const {
                return p == rhs.p;
            }

            bool operator!=(const iterator &rhs) const {
                return !(rhs == *this);
            }


        };

        iterator begin() {
            return iterator(front);
        }

        iterator end() {
            return iterator(nullptr);
        }

        const iterator begin() const {
            return iterator(front);
        }

        const iterator end() const {
            return iterator(nullptr);
        }

    };

    template<typename T>
    Queue<T>::Queue() {
        front = rear = nullptr;
    }

    template<typename T>
    Queue<T>::~Queue() {
        while (front != nullptr) {
            Node *p = front;
            front = front->next;
            delete p;
        }
    }

    template<typename T>
    void Queue<T>::enqueue(Queue<T>::value_type &&element) {
        Node *p = new Node;
        p->data = element;
        p->next = nullptr;
        if (front == nullptr) {
            front = rear = p;
        } else {
            rear->next = p;
            rear = p;
        }
    }

    template<typename T>
    typename Queue<T>::value_type &&Queue<T>::dequeue() {
        if (front == nullptr) {
            throw out_of_range("queue is empty");
        }
        Node *p = front;
        front = front->next;
        value_type data = p->data;
        delete p;
        return std::move(data);
    }

    template<typename T>
    typename Queue<T>::value_type Queue<T>::peek() {
        if (front == nullptr) {
            throw out_of_range("queue is empty");
        }
        return front->data;
    }

    template<typename T>
    bool Queue<T>::is_empty() {
        return front == nullptr;
    }

    template<typename T>
    std::ostream &Queue<T>::operator<<(std::ostream &os) const {
        Node *p = front;
        while (p != nullptr) {
            os << p->data << " ";
            p = p->next;
        }
        return os;
    }

    template<typename T>
    std::istream &Queue<T>::operator>>(std::istream &is) {
        Node *p = front;
        while (p != nullptr) {
            is >> p->data;
            p = p->next;
        }
        return is;
    }

}
#endif //DATA_STRUCTURE_QUEUE_H
