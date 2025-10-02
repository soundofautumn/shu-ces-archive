//
// Created by 邱姜铭 on 2024/1/17.
//

#ifndef DATA_STRUCTURE_MEDIAN_H
#define DATA_STRUCTURE_MEDIAN_H

#include "Heap.h"

template<class T>
class Median {
public:
    Median() : _min_heap(), _max_heap() {}

    explicit Median(int max_size) : _min_heap(max_size / 2 + 1), _max_heap(max_size / 2 + 1) {}

    void insert(const T &e) {
        if (_min_heap.empty() || e >= _min_heap.top()) {
            _min_heap.insert(e);
        } else {
            _max_heap.insert(e);
        }
        if (_min_heap.size() - _max_heap.size() > 1) {
            _max_heap.insert(_min_heap.top());
            _min_heap.pop();
        } else if (_max_heap.size() - _min_heap.size() > 1) {
            _min_heap.insert(_max_heap.top());
            _max_heap.pop();
        }
    }

    void remove(const T &e) {
        if (_min_heap.empty() || e >= _min_heap.top()) {
            _min_heap.remove(e);
        } else {
            _max_heap.remove(e);
        }
        if (_min_heap.size() - _max_heap.size() > 1) {
            _max_heap.insert(_min_heap.top());
            _min_heap.pop();
        } else if (_max_heap.size() - _min_heap.size() > 1) {
            _min_heap.insert(_max_heap.top());
            _max_heap.pop();
        }
    }

    T median() const {
        if (_min_heap.size() > _max_heap.size()) {
            return _min_heap.top();
        } else if (_min_heap.size() < _max_heap.size()) {
            return _max_heap.top();
        } else {
            return (_min_heap.top() + _max_heap.top()) / 2;
        }
    }

    void clear() {
        _min_heap.clear();
        _max_heap.clear();
    }

private:
    MinHeap<T> _min_heap;
    MaxHeap<T> _max_heap;
};

#endif //DATA_STRUCTURE_MEDIAN_H
