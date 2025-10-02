//
// Created by 邱姜铭 on 2024/4/17.
//
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include "Dictionary.h"
#include "console_utils.h"


void Dictionary::readFromFile(const std::string &filename) {
    using namespace std;
    // 清空原有数据
    entries.clear();
    entryMap.clear();
    wifstream file;
    // 读取文件时使用utf-8编码
    file.imbue(utf8_locale);
    file.open(filename, ios::in);
    if (!file.is_open()) {
        cerr << "Error: cannot open file " << filename << endl;
        return;
    }
    while (!file.eof()) {
        auto *entry = new Entry();
        file >> entry->word >> entry->meaning >> entry->partOfSpeech;
        entries.push_back(*entry);
    }
    file.close();

    // 二分查找需要有序
    std::sort(entries.begin(), entries.end(), [](const Entry &a, const Entry &b) {
        return a.word < b.word;
    });

    // 哈希查找需要构建哈希表
    for (const auto &entry: entries) {
        entryMap[entry.word] = entry;
    }
}

const std::vector<Entry> &Dictionary::getEntries() const {
    return entries;
}

void Dictionary::setAlgorithm(SearchAlgorithm _algorithm) {
    this->algorithm = _algorithm;
}

Dictionary::SearchAlgorithm Dictionary::getAlgorithm() const {
    return algorithm;
}

std::wstring Dictionary::getAlgorithmString() const {
    switch (algorithm) {
        case SEQUENTIAL:
            return L"顺序查找";
        case BINARY:
            return L"二分查找";
        case HASH:
            return L"哈希查找";
    }
}

void Dictionary::setShowFlag(bool flag) {
    this->show_flag = flag;
}

bool Dictionary::getShowFlag() const {
    return show_flag;
}

const Entry &Dictionary::getEntry(const std::wstring &word) const {
    switch (algorithm) {
        case SEQUENTIAL:
            return getEntrySequential(word);
        case BINARY:
            return getEntryBinary(word);
        case HASH:
            return getEntryHash(word);
    }
}

const Entry &Dictionary::getEntrySequential(const std::wstring &word) const {
    auto it = entries.begin();
    while (it != entries.end()) {
        if (show_flag) {
            using namespace std;
            // 显示效果
            // ... word - 1, word ,word + 1 ...
            //                ^
            size_t space_len = 0;
            wcout << "... ";
            space_len += 4;
            if (it != entries.begin()) {
                wcout << (it - 1)->word << ", ";
                space_len += (it - 1)->word.size() + 2;
            }
            wcout << it->word;
            if (it != entries.end() - 1) {
                wcout << ", " << (it + 1)->word;
            }
            wcout << " ..." << endl;
            cout << string(space_len + it->word.size() / 2 - 1, ' ') << '^' << endl;

            this_thread::sleep_for(chrono::milliseconds(50));
        }
        if (it->word == word) {
            return *it;
        }
        it++;
    }
    throw std::runtime_error("未找到该单词");
}

enum BinarySearchState {
    NO, LEFT, RIGHT, MID
};

void print_binary_search(const std::vector<Entry> &entries,
                         size_t left, size_t mid, size_t right,
                         BinarySearchState state = NO) {
    using namespace std;
    // 显示效果
    // [left, ...(+n) , mid - 1] mid [mid + 1,...(+n) , right]

    wstring left_part, mid_part, right_part;
    if ((mid - 1) > left) {
        // [left, ...(+n) , mid - 1]
        left_part = L" [" + entries[left].word +
                    L", ...(+" + to_wstring((mid - 1) - left - 1) + L") , " +
                    entries[mid - 1].word + L"] ";
    } else {
        // [left]
        left_part = L" [" + entries[left].word + L"] ";
    }
    mid_part = entries[mid].word;

    if ((mid + 1) < right) {
        // [mid + 1,...(+n) , right]
        right_part = L" [" + entries[mid + 1].word +
                     L", ...(+" + to_wstring((right - (mid + 1) - 1)) + L") , " +
                     entries[right].word + L"]";
    } else {
        // [right]
        right_part = L" [" + entries[right].word + L"]";
    }

    if (state == LEFT) {
        wcout << print_red(left_part)
              << entries[mid].word
              << right_part
              << endl;
    } else if (state == RIGHT) {
        wcout << left_part
              << entries[mid].word
              << print_red(right_part)
              << endl;
    } else if (state == MID) {
        wcout << left_part
              << print_red(entries[mid].word)
              << right_part
              << endl;
    } else {
        wcout << left_part
              << entries[mid].word
              << right_part
              << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(100));
}

const Entry &Dictionary::getEntryBinary(const std::wstring &word) const {
    size_t left = 0, right = entries.size() - 1;
    while (left <= right) {
        size_t mid = (left + right) / 2;
        if (show_flag) {
            print_binary_search(entries, left, mid, right);
        }
        if (entries[mid].word == word) {
            if (show_flag) {
                print_binary_search(entries, left, mid, right, MID);
            }
            return entries[mid];
        } else if (entries[mid].word < word) {
            if (show_flag) {
                print_binary_search(entries, left, mid, right, RIGHT);
            }
            left = mid + 1;
        } else {
            if (show_flag) {
                print_binary_search(entries, left, mid, right, LEFT);
            }
            right = mid - 1;
        }
    }
    throw std::runtime_error("未找到该单词");
}

template<class Map>
void print_hash_search(typename Map::Node **table, std::size_t size,
                       std::size_t index, const typename Map::Node *node) {
    using namespace std;

    // +-------+
    // |index-1| -> node -> null
    // | index | -> node -> null
    // |index+1| -> node -> null
    // +-------+

    // -> node1 -> node2 -> null
    auto print_node = [table, node](size_t index) {
        typename Map::Node *p = table[index];
        while (p != nullptr) {
            wcout << " -> ";
            if (p == node) {
                wcout << print_red(p->key);
            } else {
                wcout << p->key;
            }
            p = p->next;
        }
        wcout << " -> null" << endl;
    };

    wcout << "+------+" << endl;
    if (index == 0) {
        wcout << "|      |" << endl;
    } else {
        wcout << "| " << setw(4) << index - 1 << " |";
        print_node(index - 1);
    }
    wcout << "| " << setw(4) << index << " |";
    print_node(index);
    if (index == size - 1) {
        wcout << "|      |" << endl;
    } else {
        wcout << "| " << setw(4) << index + 1 << " |";
        print_node(index + 1);
    }
    wcout << "+------+" << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
}

const Entry &Dictionary::getEntryHash(const std::wstring &word) const {
    try {
        if (show_flag) {
            return entryMap.at(word, print_hash_search<decltype(entryMap)>);
        } else {
            return entryMap.at(word);
        }
    } catch (const std::runtime_error &e) {
        throw std::runtime_error("未找到该单词");
    }
}

std::size_t Dictionary::size() const {
    return entries.size();
}

