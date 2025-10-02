//
// Created by 邱姜铭 on 2024/4/29.
//

#ifndef ZPP_DATA_STRUCTURE_SORTS_H
#define ZPP_DATA_STRUCTURE_SORTS_H

#include <vector>
#include <string>

namespace sort {

    enum class SortAlgorithm {
        QUICK_SORT,
        SHELL_SORT,
        BUCKET_SORT,
        HEAP_SORT,
        MERGE_SORT,
        STD_SORT,
    };

    void quickSort(std::vector<std::string> &entries);

    void shellSort(std::vector<std::string> &entries);

    void bucketSort(std::vector<std::string> &entries);

    void heapSort(std::vector<std::string> &entries);

    void mergeSort(std::vector<std::string> &entries);

    void stdSort(std::vector<std::string> &entries);

    typedef void sort_func(std::vector<std::string> &);

    inline SortAlgorithm sort_algorithms[] = {
            SortAlgorithm::QUICK_SORT,
            SortAlgorithm::SHELL_SORT,
            SortAlgorithm::BUCKET_SORT,
            SortAlgorithm::HEAP_SORT,
            SortAlgorithm::MERGE_SORT,
            SortAlgorithm::STD_SORT,
    };

    inline sort_func *sort_funcs[] = {
            quickSort,
            shellSort,
            bucketSort,
            heapSort,
            mergeSort,
            stdSort,
    };

    inline const std::wstring sort_names[] = {
            L"快速排序",
            L"希尔排序",
            L"桶排序",
            L"堆排序",
            L"归并排序",
            L"标准库排序",
    };

}


#endif //ZPP_DATA_STRUCTURE_SORTS_H
