//
// Created by 邱姜铭 on 2024/4/29.
//

#ifndef ZPP_DATA_STRUCTURE_DICTREADER_H
#define ZPP_DATA_STRUCTURE_DICTREADER_H

#include <string>
#include <vector>
#include "sorts.h"

using namespace sort;


class DictReader {
private:
    SortAlgorithm _algorithm = SortAlgorithm::QUICK_SORT;
    std::vector<std::string> _entries;
public:
    DictReader();

    DictReader(const DictReader &reader);

    DictReader &operator=(const DictReader &reader);

    void readFromFile(const std::string &filename);

    void sort();

    [[nodiscard]]
    const std::vector<std::string> &getEntries() const;

    void setAlgorithm(SortAlgorithm algorithm);

    [[nodiscard]]
    SortAlgorithm getAlgorithm() const;

    [[nodiscard]]
    std::wstring getAlgorithmString() const;
};


#endif //ZPP_DATA_STRUCTURE_DICTREADER_H
