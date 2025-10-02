//
// Created by 邱姜铭 on 2024/4/17.
//

#ifndef ZPP_DATA_STRUCTURE_DICTIONARY_H
#define ZPP_DATA_STRUCTURE_DICTIONARY_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "string_utils.h"
#include "HashMap.h"

struct Entry {
    // 单词
    std::wstring word;
    // 词义
    std::wstring meaning;
    // 词性
    std::wstring partOfSpeech;

    friend std::wostream &operator<<(std::wostream &os, const Entry &entry) {
        os << entry.word << L"\n"
           << entry.partOfSpeech << L" " << entry.meaning;
        return os;
    }

};


class Dictionary {

public:
    enum SearchAlgorithm {
        SEQUENTIAL,
        BINARY,
        HASH
    };
private:

    SearchAlgorithm algorithm = HASH;

    bool show_flag = false;

    std::vector<Entry> entries;

    HashMap<std::wstring, Entry> entryMap;

public:
    void readFromFile(const std::string &filename);

    const std::vector<Entry> &getEntries() const;

    void setAlgorithm(SearchAlgorithm _algorithm);

    SearchAlgorithm getAlgorithm() const;

    std::wstring getAlgorithmString() const;

    void setShowFlag(bool flag);

    bool getShowFlag() const;

    const Entry &getEntry(const std::wstring &word) const;

    // 顺序查找算法
    const Entry &getEntrySequential(const std::wstring &word) const;

    // 二分查找
    const Entry &getEntryBinary(const std::wstring &word) const;

    // 哈希查找
    const Entry &getEntryHash(const std::wstring &word) const;

    std::size_t size() const;

};


#endif //ZPP_DATA_STRUCTURE_DICTIONARY_H
