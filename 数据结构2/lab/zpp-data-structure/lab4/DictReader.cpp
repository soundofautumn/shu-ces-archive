//
// Created by 邱姜铭 on 2024/4/29.
//

#include <fstream>
#include <iostream>
#include <string>
#include "DictReader.h"

DictReader::DictReader() = default;

DictReader::DictReader(const DictReader &reader) {
    _algorithm = reader._algorithm;
    _entries = reader._entries;
}

DictReader &DictReader::operator=(const DictReader &reader) = default;

void DictReader::readFromFile(const std::string &filename) {
    using namespace std;
    // 清空原有数据
    _entries.clear();
    fstream file;
    file.open(filename, ios::in);
    if (!file.is_open()) {
        cerr << "Error: cannot open file " << filename << endl;
        return;
    }
    while (!file.eof()) {
        string entry;
        file >> entry;
        _entries.push_back(entry);
    }
    file.close();
}

void DictReader::sort() {
    sort::sort_funcs[static_cast<int>(_algorithm)](_entries);
}

const std::vector<std::string> &DictReader::getEntries() const {
    return _entries;
}

void DictReader::setAlgorithm(SortAlgorithm algorithm) {
    _algorithm = algorithm;
}

SortAlgorithm DictReader::getAlgorithm() const {
    return _algorithm;
}

std::wstring DictReader::getAlgorithmString() const {
    return sort_names[static_cast<int>(_algorithm)];
}


