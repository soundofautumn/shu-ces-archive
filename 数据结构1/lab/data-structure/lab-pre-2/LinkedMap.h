//
// Created by 邱姜铭 on 2023/12/13.
//

#ifndef DATA_STRUCTURE_LINKEDMAP_H
#define DATA_STRUCTURE_LINKEDMAP_H

#include <iterator>
#include "common_exception.h"

namespace flight {
    template<typename K, typename V>
    class LinkedMap {
    private:
        typedef K key_type;
        typedef V value_type;
        struct Node {
            key_type key;
            value_type value;
            Node *next;
        } *head;
    public:
        LinkedMap();

        ~LinkedMap();

        void insert(key_type key, value_type value);

        value_type &get(key_type key) const;

        value_type &operator[](key_type key) const;

        value_type &getOrPut(key_type key, value_type value);

        void remove(key_type key);

        bool contains(key_type key);

        bool operator==(const LinkedMap &rhs) const;

        std::ostream &operator<<(std::ostream &os) const;

        friend std::ostream &operator<<(std::ostream &os, const LinkedMap &map) {
            return map.operator<<(os);
        }

        std::istream &operator>>(std::istream &is);

        friend std::istream &operator>>(std::istream &is, LinkedMap &map) {
            return map.operator>>(is);
        }

        class iterator : public std::iterator<std::forward_iterator_tag, Node> {
        public:
            struct pair {
                key_type &key;
                value_type &value;

                pair(key_type &key, value_type &value) : key(key), value(value) {
                }
            };

        private:
            Node *p;
        public:
            explicit iterator(Node *p) : p(p) {}

            iterator &operator++() {
                p = p->next;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            bool operator==(const iterator &rhs) const {
                return p == rhs.p;
            }

            bool operator!=(const iterator &rhs) const {
                return !(rhs == *this);
            }

            const pair &operator*() const {
                return *(new pair(p->key, p->value));
            }

            pair *operator->() const {
                return new pair(p->key, p->value);
            }
        };

        iterator begin();

        iterator end();
    };

    template<typename K, typename V>
    LinkedMap<K, V>::LinkedMap() {
        head = nullptr;
    }

    template<typename K, typename V>
    LinkedMap<K, V>::~LinkedMap() {
        while (head != nullptr) {
            Node *p = head;
            head = head->next;
            delete p;
        }
    }

    template<typename K, typename V>
    void LinkedMap<K, V>::insert(key_type key, value_type value) {
        Node *p = head;
        while (p != nullptr) {
            if (p->key == key) {
                p->value = std::move(value);
                return;
            }
            p = p->next;
        }
        p = new Node;
        p->key = std::move(key);
        p->value = std::move(value);
        p->next = head;
        head = p;
    }

    template<typename K, typename V>
    typename LinkedMap<K, V>::value_type &LinkedMap<K, V>::get(key_type key) const {
        Node *p = head;
        while (p != nullptr) {
            if (p->key == key) {
                return p->value;
            }
            p = p->next;
        }
        throw key_not_found("Key not found");
    }

    template<typename K, typename V>
    typename LinkedMap<K, V>::value_type &LinkedMap<K, V>::operator[](key_type key) const {
        return get(key);
    }

    template<typename K, typename V>
    typename LinkedMap<K, V>::value_type &LinkedMap<K, V>::getOrPut(key_type key, value_type value) {
        try {
            return get(key);
        } catch (key_not_found &e) {
            insert(key, value);
            return get(key);
        }
    }

    template<typename K, typename V>
    void LinkedMap<K, V>::remove(key_type key) {
        Node *p = head;
        Node *pre = nullptr;
        while (p != nullptr) {
            if (p->key == key) {
                if (pre == nullptr) {
                    head = p->next;
                } else {
                    pre->next = p->next;
                }
                delete p;
                return;
            }
            pre = p;
            p = p->next;
        }
        throw key_not_found("Key not found");
    }

    template<typename K, typename V>
    bool LinkedMap<K, V>::contains(key_type key) {
        Node *p = head;
        while (p != nullptr) {
            if (p->key == key) {
                return true;
            }
            p = p->next;
        }
        return false;
    }

    template<typename K, typename V>
    typename LinkedMap<K, V>::iterator LinkedMap<K, V>::begin() {
        return iterator(head);
    }

    template<typename K, typename V>
    typename LinkedMap<K, V>::iterator LinkedMap<K, V>::end() {
        return iterator(nullptr);
    }

    template<typename K, typename V>
    bool LinkedMap<K, V>::operator==(const LinkedMap &rhs) const {
        Node *p = head;
        Node *q = rhs.head;
        while (p != nullptr && q != nullptr) {
            if (p->key != q->key || p->value != q->value) {
                return false;
            }
            p = p->next;
            q = q->next;
        }
        return p == nullptr && q == nullptr;
    }

    template<typename K, typename V>
    std::ostream &LinkedMap<K, V>::operator<<(std::ostream &os) const {
        Node *p = head;
        while (p != nullptr) {
            os << p->key << " " << p->value << std::endl;
            p = p->next;
        }
        return os;
    }

    template<typename K, typename V>
    std::istream &LinkedMap<K, V>::operator>>(std::istream &is) {
        Node *p = head;
        while (p != nullptr) {
            is >> p->key >> p->value;
            p = p->next;
        }
        return is;
    }
}
#endif //DATA_STRUCTURE_LINKEDMAP_H
