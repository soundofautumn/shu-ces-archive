//
// Created by 邱姜铭 on 2023/12/13.
//

#ifndef DATA_STRUCTURE_SEQLIST_H
#define DATA_STRUCTURE_SEQLIST_H

#include <iterator>
#include <iostream>
#include "common_exception.h"


namespace flight {
    template<typename T>
    class SeqList {
    private:
        typedef T value_type;
        typedef int size_type;
        value_type *data;
        size_type length;
        size_type maxSize;
    public:
        explicit SeqList(size_type size = 10);

        ~SeqList();

        void clear();

        bool is_empty() const;

        bool is_full() const;

        size_type get_length();

        value_type get(size_type i);

        size_type locate(const value_type &x);

        void insert(value_type &&x, size_type i = 0);

        value_type remove(size_type i);

        std::ostream &operator<<(std::ostream &os) const;

        friend std::ostream &operator<<(std::ostream &os, const SeqList &list) {
            return list.operator<<(os);
        }

        std::istream &operator>>(std::istream &is);

        friend std::istream &operator>>(std::istream &is, SeqList &list) {
            return list.operator>>(is);
        }

        class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
        private:
            value_type *p;
        public:
            explicit iterator(value_type *p) : p(p) {}

            iterator &operator++() {
                ++p;
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

            value_type &operator*() const {
                return *p;
            }
        };

        iterator begin() const {
            return iterator(data);
        }

        iterator end() const {
            return iterator(data + length);
        }
    };

    template<typename T>
    SeqList<T>::SeqList(size_type size):data(new value_type[size]), maxSize(size), length(0) {
    }

    template<typename T>
    SeqList<T>::~SeqList() {
        if (length > 0)
            delete[] data;
    }

    template<typename T>
    void SeqList<T>::clear() {
        length = 0;
    }

    template<typename T>
    bool SeqList<T>::is_empty() const {
        return length == 0;
    }

    template<typename T>
    bool SeqList<T>::is_full() const {
        return length == maxSize;
    }

    template<typename T>
    typename SeqList<T>::size_type SeqList<T>::get_length() {
        return length;
    }

    template<typename T>
    typename SeqList<T>::value_type SeqList<T>::get(size_type i) {
        if (i < 0 || i >= length) {
            throw out_of_range("out of range");
        }
        return data[i];
    }

    template<typename T>
    typename SeqList<T>::size_type SeqList<T>::locate(const value_type &x) {
        for (size_type i = 0; i < length; ++i) {
            if (data[i] == x) {
                return i;
            }
        }
        return -1;
    }

    template<typename T>
    void SeqList<T>::insert(value_type &&x, size_type i) {
        if (length == maxSize) {
            throw overflow("overflow");
        }
        if (i < 0 || i > length) {
            throw out_of_range("out of range");
        }
        for (size_type j = length; j > i; --j) {
            data[j] = std::move(data[j - 1]);
        }
        data[i] = std::move(x);
        ++length;
    }

    template<typename T>
    typename SeqList<T>::value_type SeqList<T>::remove(size_type i) {
        if (length == 0) {
            throw underflow("underflow");
        }
        if (i < 0 || i >= length) {
            throw out_of_range("out of range");
        }
        value_type tmp = std::move(data[i]);
        for (size_type j = i; j < length - 1; ++j) {
            data[j] = std::move(data[j + 1]);
        }
        --length;
        return tmp;
    }

    template<typename T>
    std::ostream &SeqList<T>::operator<<(std::ostream &os) const {
        for (size_type i = 0; i < length; ++i) {
            os << data[i] << " ";
        }
        return os;
    }

    template<typename T>
    std::istream &SeqList<T>::operator>>(std::istream &is) {
        for (size_type i = 0; i < length; ++i) {
            is >> data[i];
        }
        return is;
    }

}


#endif //DATA_STRUCTURE_SEQLIST_H
