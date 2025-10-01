// SortStrings.h
#ifndef SORTSTRINGS_H
#define SORTSTRINGS_H
#include <iostream>
using namespace std;

#define NUM 20

// 如下3个函数的功能：通过给定的字符串数组，构造不同存放方式的动态C-字符串数组
void GetStrings0(char**& dest, const char* const source[], int n);
void GetStrings1(char**& dest, const char* const source[], int n);
void GetStrings2(char**& dest, const char* const source[], int n);

void FreeStrings(char**& strs, int n, bool flag = false);			// 释放动态C-字符串数（flag为true指连续存放，flase指不连续存放）

void BubbleA(char (*strs)[NUM], int n);								// 通过交换C-字符串的内容，实现排序
void BubbleA(char** strs, int n);									// 通过交换C-字符串的内容，实现排序
void BubbleB(char** strs, int n);									// 通过交换C-字符串的指针

template <typename T> void ShowStrings(const char* prompt, const T* const strs, int n)
{																	// 此处T可以是char*, char (*)[NUM]
	if (n > 0)
		cout << prompt << strs[0];
	for (int i = 1; i < n; i++)
		cout << ", " << strs[i];
	cout << endl;
}
#endif
