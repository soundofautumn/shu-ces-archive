//
// Created by 邱姜铭 on 2023/9/27.
//
#include "MyString.h"
#include "my_assert.h"


using namespace std;


int main() {
    cout << "默认构造函数测试" << endl;
    run(MyString default_construct = MyString())
    my_assert(default_construct, "")
    my_assert(default_construct.length(), 0)
    cout << "空指针测试" << endl;
    run(MyString nullptrString(nullptr, 0))
    my_assert(nullptrString, "")
    my_assert(nullptrString.length(), 0)
    cout << "默认构造和空指针等价测试" << endl;
    my_assert(default_construct == nullptrString, true)

    cout << "=======================================" << endl;
    run(MyString helloWord("Hello Word!", 11))
    cout << "字符串输出测试" << endl;
    my_assert(helloWord, "Hello Word!")
    cout << "字符串拼接测试" << endl;
    cout << "operator+运算符测试" << endl;
    my_assert(nullptrString + helloWord, "Hello Word!")
    cout << "operator+=运算符测试" << endl;
    run(nullptrString += helloWord)
    my_assert(nullptrString, "Hello Word!")
    cout << "operator=运算符测试" << endl;
    run(nullptrString = MyString(nullptr, 0))
    my_assert(nullptrString, "")
    cout << "自赋值测试" << endl;
    run(nullptrString = nullptrString)
    my_assert(nullptrString, "")
    cout << "空字符串应和空指针等价" << endl;
    run(MyString emptyString("", 0))
    my_assert(emptyString, "")

    cout << "=======================================" << endl;
    run(MyString biggerString("abc", 3))
    cout << "拷贝构造函数测试" << endl;
    run(MyString anotherBiggerString(biggerString))
    my_assert(anotherBiggerString, "abc")
    cout << "移动构造函数测试" << endl;
    run(MyString movedBiggerString(std::move(anotherBiggerString)))
    my_assert(movedBiggerString, "abc")
    run(MyString smallerString("ab", 2))
    cout << "比较测试" << endl;
    my_assert(biggerString == smallerString, false)
    my_assert(biggerString < smallerString, false)
    my_assert(biggerString > smallerString, true)
    my_assert(biggerString <= smallerString, false)
    my_assert(biggerString >= smallerString, true)
    my_assert(biggerString != smallerString, true)
    cout << "下标访问测试" << endl;
    my_assert(biggerString[0], 'a')
    cout << "下标访问异常测试" << endl;
    my_assert_throws(biggerString[3], std::out_of_range)
    return 0;
}
