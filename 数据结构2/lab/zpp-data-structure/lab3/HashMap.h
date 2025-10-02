//
// Created by 邱姜铭 on 2024/4/18.
//

#ifndef ZPP_DATA_STRUCTURE_HASHMAP_H
#define ZPP_DATA_STRUCTURE_HASHMAP_H

#include <functional>


template<typename K, typename V>
class HashMap {
public:
    typedef std::size_t size_type;
    
    typedef K key_type;
    typedef V value_type;

    struct Node {
        key_type key;
        value_type value;
        Node *next;

        Node(const key_type &key, const value_type &value) : key(key), value(value), next(nullptr) {}
    };

private:
    Node **table;
    // 容量
    size_type capacity;
    // 大小
    size_type size;
public:

    HashMap() : capacity(16), size(0) {
        table = new Node *[capacity];
        for (size_type i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    ~HashMap() {
        for (size_type i = 0; i < capacity; i++) {
            Node *node = table[i];
            while (node != nullptr) {
                Node *next = node->next;
                delete node;
                node = next;
            }
        }
        delete[] table;
    }

    size_type hash(const key_type &key) const {
        return std::hash<key_type>()(key) % capacity;
    }

    void resize() {
        const size_type oldCapacity = capacity;
        const size_type newCapacity = capacity * 2;
        capacity = newCapacity;
        Node **newTable = new Node *[newCapacity];
        for (size_type i = 0; i < newCapacity; i++) {
            newTable[i] = nullptr;
        }
        // 将旧表中的元素复制到新表中
        for (size_type i = 0; i < oldCapacity; i++) {
            Node *node = table[i];
            while (node != nullptr) {
                Node *next = node->next;
                size_type index = hash(node->key);
                node->next = newTable[index];
                newTable[index] = node;
                node = next;
            }
        }
        delete[] table;
        table = newTable;
    }

    void clear() {
        for (size_type i = 0; i < capacity; i++) {
            Node *node = table[i];
            while (node != nullptr) {
                Node *next = node->next;
                delete node;
                node = next;
            }
            table[i] = nullptr;
        }
        size = 0;
    }

    bool contains(const key_type &key) const {
        size_type index = hash(key);
        Node *node = table[index];
        while (node != nullptr) {
            if (node->key == key) {
                return true;
            }
            node = node->next;
        }
        return false;
    }

    value_type &at(const key_type &key) const {
        size_type index = hash(key);
        Node *node = table[index];
        while (node != nullptr) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        throw std::runtime_error("Key not found");
    }

    typedef std::function<void(Node **table, size_type size, size_type index, const Node *node)> VisitFunction;

    value_type &at(const key_type &key, VisitFunction visit) const {
        size_type index = hash(key);
        Node *node = table[index];
        visit(table, capacity, index, node);
        while (node != nullptr) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
            visit(table, capacity, index, node);
        }
        throw std::runtime_error("Key not found");
    }


    // 运算符重载
    value_type &operator[](const key_type &key) {
        size_type index = hash(key);
        Node *node = table[index];
        while (node != nullptr) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        if (size >= capacity) {
            resize();
            index = hash(key);
        }
        Node *newNode = new Node(key, value_type());
        newNode->next = table[index];
        table[index] = newNode;
        size++;
        return newNode->value;
    }


};


#endif //ZPP_DATA_STRUCTURE_HASHMAP_H
