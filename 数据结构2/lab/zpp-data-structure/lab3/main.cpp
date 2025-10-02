//
// Created by 邱姜铭 on 2024/4/17.
//
#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include "Dictionary.h"
#include "console_utils.h"

using namespace std;

Dictionary dictionary;

const static int N = 100;

void load();

void test(int n = N);

void test_all();

void print_menu() {
    wcout << L"==========================================" << endl;
    wcout << L"当前查找算法：" << print_yellow(dictionary.getAlgorithmString()) << endl;
    wcout << L"当前查找过程：" << print_yellow((dictionary.getShowFlag() ? L"显示" : L"不显示")) << endl;
    wcout << L"直接输入单词进行查找" << endl;
    wcout << L"/load 重新加载词典" << endl;
    wcout << L"/show 显示查找过程" << endl;
    wcout << L"/hide 不显示查找过程" << endl;
    wcout << L"/set seq(uential) 设置为顺序查找" << endl;
    wcout << L"/set bin(ary) 设置为二分查找" << endl;
    wcout << L"/set hash 设置为哈希查找" << endl;
    wcout << L"/test 测试查找时间" << endl;
    wcout << L"/testall 测试查找时间（全部）" << endl;
    wcout << L"/exit 退出" << endl;
    wcout << L"==========================================" << endl;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "zh_CN.UTF-8");
#elif defined(__APPLE__) || defined(__linux__)
    wcout.imbue(utf8_locale);
#endif
    load();
    while (true) {
        print_menu();
        wstring command;
        wcin >> command;
        if (command == L"/load") {
            load();
        } else if (command == L"/show") {
            dictionary.setShowFlag(true);
            wcout << L"显示查找过程" << endl;
        } else if (command == L"/hide") {
            dictionary.setShowFlag(false);
            wcout << L"不显示查找过程" << endl;
        } else if (command == L"/set") {
            wstring algorithm;
            wcin >> algorithm;
            if (algorithm == L"sequential" || algorithm == L"seq") {
                dictionary.setAlgorithm(Dictionary::SEQUENTIAL);
                wcout << L"设置为顺序查找" << endl;
            } else if (algorithm == L"binary" || algorithm == L"bin") {
                dictionary.setAlgorithm(Dictionary::BINARY);
                wcout << L"设置为二分查找" << endl;
            } else if (algorithm == L"hash") {
                dictionary.setAlgorithm(Dictionary::HASH);
                wcout << L"设置为哈希查找" << endl;
            } else {
                wcout << L"未知算法" << endl;
            }
        } else if (command == L"/test") {
            test();
        } else if (command == L"/testall") {
            test_all();
        } else if (command == L"/exit") {
            break;
        } else {
            try {
                wcout << dictionary.getEntry(command) << endl;
            } catch (const runtime_error &e) {
                wcout << L"未找到该单词" << endl;
            }
        }
        PAUSE
        CLEAR
    }
    return 0;
}

void load() {
    dictionary.readFromFile("dictionary.txt");
    wcout << L"加载完成，共" << dictionary.size() << L"个词条" << endl;
}


void test(int n) {
    using namespace chrono;

    //从词典文件中随机选出100个单词作为待查找单词列表（10分），用以上两种查找算法进行批量的单词查找，并显示各自的批量查找总时间（20分）
    vector<wstring> words;
    for (const auto &entry: dictionary.getEntries()) {
        words.push_back(entry.word);
    }

    // 随机打乱
    random_device rd;
    mt19937 g(rd());
    shuffle(words.begin(), words.end(), g);

    // 测试过程 先把显示关了
    const bool show_flag = dictionary.getShowFlag();
    dictionary.setShowFlag(false);
    const Dictionary::SearchAlgorithm algorithm = dictionary.getAlgorithm();

    const Dictionary::SearchAlgorithm algorithms[] = {Dictionary::SEQUENTIAL, Dictionary::BINARY, Dictionary::HASH};

    for (auto alg: algorithms) {
        dictionary.setAlgorithm(alg);
        auto start = high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            try {
                dictionary.getEntry(words[i]);
            } catch (const runtime_error &e) {
                wcout << L"未找到该单词" << endl;
                wcout << words[i] << endl;
            }
        }
        auto end = high_resolution_clock::now();
        wcout << dictionary.getAlgorithmString()
              << L"总时间：" << duration_cast<microseconds>(end - start).count() << L"微秒" << endl;
    }
    // 测试结束后再设置回去
    dictionary.setShowFlag(show_flag);
    dictionary.setAlgorithm(algorithm);
}

void test_all() {
    test(static_cast<int>(dictionary.size()));
}