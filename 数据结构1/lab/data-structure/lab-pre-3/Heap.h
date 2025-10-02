//
// Created by 邱姜铭 on 2024/1/17.
//

#ifndef DATA_STRUCTURE_HEAP_H
#define DATA_STRUCTURE_HEAP_H

template<class T>
class Heap;

template<class T>
class MinHeap : public Heap<T> {
public:
    explicit MinHeap(int max_size = 1 << 8) : Heap<T>(max_size) {}

protected:
    int cmp(const T &a, const T &b) override {
        return b - a;
    }
};

template<class T>
class MaxHeap : public Heap<T> {
public:
    explicit MaxHeap(int max_size = 1 << 8) : Heap<T>(max_size) {}

protected:
    int cmp(const T &a, const T &b) override {
        return a - b;
    }
};

template<class T>
class Heap {
public:
    explicit Heap(int max_size = 1 << 8);

    ~Heap() { delete[] _arr; }

    void insert(const T &e);

    void remove(const T &e);

    void pop();

    T top() const;

    bool empty() const { return _size == 0; }

    bool full() const { return _size == _max_size; }

    int size() const { return _size; }

    void resize(int new_size);

    void traverse(void (*visit)(const T &)) const;

    void clear() { _size = 0; }

protected:
    virtual int cmp(const T &a, const T &b) = 0;

private:
    T *_arr;
    int _size;
    int _max_size;

    void filter_down(int start);

    void filter_up(int end);
};

template<class T>
Heap<T>::Heap(int max_size) {
    _max_size = max_size;
    _arr = new T[_max_size];
    _size = 0;
}

template<class T>
void Heap<T>::insert(const T &e) {
    if (full()) {
        resize(_max_size * 2);
    }
    _arr[_size] = e;
    filter_up(_size);
    ++_size;
}

template<class T>
void Heap<T>::remove(const T &e) {
    int i = 0;
    while (i < _size && _arr[i] != e) {
        ++i;
    }
    if (i == _size) {
        return;
    }
    _arr[i] = _arr[_size - 1];
    --_size;
    filter_down(i);
}

template<class T>
void Heap<T>::pop() {
    if (empty()) {
        return;
    }
    _arr[0] = _arr[_size - 1];
    --_size;
    filter_down(0);
}

template<class T>
T Heap<T>::top() const {
    if (empty()) {
        return T();
    }
    return _arr[0];
}

template<class T>
void Heap<T>::resize(int new_size) {
    if (new_size <= _max_size) {
        return;
    }
    T *new_arr = new T[new_size];
    for (int i = 0; i < _size; ++i) {
        new_arr[i] = _arr[i];
    }
    delete[] _arr;
    _arr = new_arr;
    _max_size = new_size;
}

template<class T>
void Heap<T>::traverse(void (*visit)(const T &)) const {
    for (int i = 0; i < _size; ++i) {
        visit(_arr[i]);
    }
}

template<class T>
void Heap<T>::filter_down(int start) {
    int i = start, j;
    T temp = _arr[i];
    j = 2 * i + 1;
    while (j <= _size - 1) {
        if (j < _size - 1 && cmp(_arr[j], _arr[j + 1]) < 0) {
            ++j;
        }
        if (cmp(temp, _arr[j]) >= 0) {
            break;
        } else {
            _arr[i] = _arr[j];
            i = j;
            j = 2 * j + 1;
        }
    }
    _arr[i] = temp;
}

template<class T>
void Heap<T>::filter_up(int end) {
    int j = end, i;
    T temp = _arr[j];
    i = (j - 1) / 2;
    while (j > 0) {
        if (cmp(_arr[i], temp) >= 0) {
            break;
        } else {
            _arr[j] = _arr[i];
            j = i;
            i = (j - 1) / 2;
        }
        _arr[j] = temp;
    }
}


#endif //DATA_STRUCTURE_HEAP_H
