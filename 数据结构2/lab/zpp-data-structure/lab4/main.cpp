//
// Created by 邱姜铭 on 2024/4/29.
//
#include "DictReader.h"
#include <chrono>
#include <locale>
#include <iostream>
#include <codecvt>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

bool check_sort(const vector<string> &entries);

void save_to_file(const vector<string> &entries,
                  const string &filename,
                  const chrono::duration<double> &duration,
                  const sort::SortAlgorithm &algorithm);

const static locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>);

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "zh_CN.UTF-8");
#elif defined(__APPLE__) || defined(__linux__)
    wcout.imbue(utf8_locale);
#endif
    DictReader reader;
    reader.readFromFile("dictrandom.txt");
    for (SortAlgorithm algorithm: sort_algorithms) {
        DictReader newReader = DictReader(reader);
        newReader.setAlgorithm(algorithm);
        auto begin = chrono::high_resolution_clock::now();
        newReader.sort();
        auto end = chrono::high_resolution_clock::now();
        if (!check_sort(newReader.getEntries())) {
            wcerr << "Error: " << newReader.getAlgorithmString() << " failed" << endl;
            return 1;
        }
        wcout << newReader.getAlgorithmString() << " time: "
              << chrono::duration_cast<chrono::microseconds>(end - begin).count() << L"微秒" << endl;
        save_to_file(newReader.getEntries(), "dictsorted" + to_string(1 + static_cast<int>(algorithm)) + ".txt",
                     end - begin, algorithm);
    }

}

bool check_sort(const vector<string> &entries) {
    for (size_t i = 1; i < entries.size(); i++) {
        if (entries[i - 1] > entries[i]) {
            return false;
        }
    }
    return true;
}

wstring utf8_to_wstring(const string &str) {
    wstring_convert<codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(str);
}

void save_to_file(const vector<string> &entries,
                  const string &filename,
                  const chrono::duration<double> &duration,
                  const sort::SortAlgorithm &algorithm) {
    wofstream file;
    // f覆盖
    file.open(filename, ios::out);
    file.imbue(utf8_locale);
    if (!file.is_open()) {
        cerr << "Error: cannot open file " << filename << endl;
        return;
    }
    file << "=========="
         << L"第五组 第三次实验"
         << sort::sort_names[static_cast<int>(algorithm)]
         << "==========" << endl;
    for (const string &entry: entries) {
        file << utf8_to_wstring(entry) << endl;
    }
    // =========xxx.xxx 秒============
    file << L"==========" << duration.count() << L"秒==========" << endl;
    file.close();
}