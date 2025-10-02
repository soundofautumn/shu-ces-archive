//
// Created by 邱姜铭 on 2024/4/29.
//

#include <string>
#include <algorithm>
#include "sorts.h"

using namespace std;

void quickSort(std::vector<string> &entries, size_t left, size_t right);

void sort::quickSort(std::vector<string> &entries) {
    ::quickSort(entries, 0, entries.size() - 1);
}

void quickSort(std::vector<string> &entries, size_t left, size_t right) {
    if (left >= right) {
        return;
    }
    string pivot = entries[(left + right) / 2];
    size_t i = left, j = right;
    while (i <= j) {
        while (entries[i] < pivot) {
            i++;
        }
        while (entries[j] > pivot) {
            j--;
        }
        if (i <= j) {
            swap(entries[i], entries[j]);
            i++;
            j--;
        }
    }
    quickSort(entries, left, j);
    quickSort(entries, i, right);
}

void sort::shellSort(std::vector<string> &entries) {
    size_t n = entries.size();
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i++) {
            string temp = entries[i];
            size_t j;
            for (j = i; j >= gap && entries[j - gap] > temp; j -= gap) {
                entries[j] = entries[j - gap];
            }
            entries[j] = temp;
        }
    }
}

void sort::bucketSort(std::vector<string> &entries) {
    size_t n = entries.size();
    if (n == 0) {
        return;
    }
    vector<vector<string>> buckets(256);
    for (const string &entry: entries) {
        buckets[entry[0]].push_back(entry);
    }
    entries.clear();
    for (vector<string> &bucket: buckets) {
        if (bucket.empty()) {
            continue;
        }
        stdSort(bucket);
        entries.insert(entries.end(), bucket.begin(), bucket.end());
    }
}

void heapify(std::vector<string> &entries, size_t n, size_t i);

void sort::heapSort(std::vector<string> &entries) {
    size_t n = entries.size();
    for (size_t i = n / 2; i > 0; i--) {
        heapify(entries, n, i - 1);
    }
    for (size_t i = n - 1; i > 0; i--) {
        swap(entries[0], entries[i]);
        heapify(entries, i, 0);
    }
}

void heapify(std::vector<string> &entries, size_t n, size_t i) {
    size_t largest = i;
    size_t l = 2 * i + 1;
    size_t r = 2 * i + 2;
    if (l < n && entries[l] > entries[largest]) {
        largest = l;
    }
    if (r < n && entries[r] > entries[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(entries[i], entries[largest]);
        heapify(entries, n, largest);
    }
}

void merge(std::vector<string> &entries, size_t left, size_t mid, size_t right);

void mergeSort(std::vector<string> &entries, size_t left, size_t right);

void sort::mergeSort(std::vector<std::string> &entries) {
    ::mergeSort(entries, 0, entries.size() - 1);
}

void mergeSort(std::vector<string> &entries, size_t left, size_t right) {
    if (left >= right) {
        return;
    }
    size_t mid = left + (right - left) / 2;
    mergeSort(entries, left, mid);
    mergeSort(entries, mid + 1, right);
    merge(entries, left, mid, right);
}

void merge(std::vector<string> &entries, size_t left, size_t mid, size_t right) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;
    vector<string> L(n1), R(n2);
    for (size_t i = 0; i < n1; i++) {
        L[i] = entries[left + i];
    }
    for (size_t i = 0; i < n2; i++) {
        R[i] = entries[mid + 1 + i];
    }
    size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            entries[k] = L[i];
            i++;
        } else {
            entries[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        entries[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        entries[k] = R[j];
        j++;
        k++;
    }

}

void sort::stdSort(std::vector<std::string> &entries) {
    std::sort(entries.begin(), entries.end());
}
