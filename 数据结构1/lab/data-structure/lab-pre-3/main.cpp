//
// Created by 邱姜铭 on 2024/1/17.
//
#include <iostream>
#include <fstream>
#include <ctime>
#include "Median.h"

using namespace std;

void test_by_cin();

void test_by_file();

int main() {
    while (true) {
        cout << "0. exit" << endl;
        cout << "1. cin" << endl;
        cout << "2. file" << endl;
        char c;
        cin >> c;
        switch (c) {
            case '1':
                test_by_cin();
                break;
            case '2':
                test_by_file();
                break;
            case '0':
            default:
                return 0;
        }
    }
}

void test_by_cin() {
    Median<int> median;
    while (true) {
        cout << "0. exit" << endl;
        cout << "1. insert" << endl;
        cout << "2. remove" << endl;
        cout << "3. median" << endl;
        char c;
        cin >> c;
        switch (c) {
            case '1': {
                cout << "n: ";
                int n;
                cin >> n;
                for (int i = 0; i < n; ++i) {
                    int e;
                    cin >> e;
                    median.insert(e);
                }
                break;
            }
            case '2': {
                int e;
                cin >> e;
                median.remove(e);
                break;
            }
            case '3':
                cout << median.median() << endl;
                break;
            case '0':
            default:
                return;
        }
    }
}

void test_by_file() {

    ifstream file("median.txt");

    // 30万
    const int N = 3E5;
    clock_t start = clock();
    Median<int> median(N);
    for (int i = 0; i < N; ++i) {
        int e;
        file >> e;
        median.insert(e);
    }
    int result = median.median();
    clock_t end = clock();
    cout << result << endl;
    cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << "s" << endl;
    file.close();
}