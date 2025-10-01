#include <iostream>
#include <sstream>
#include "MyMathVector.h"
#include "MyString.h"
#include "my_assert.h"

using namespace std;

void testMyMathVector();

void testMyString();

void jointTest();

int main() {
    testMyMathVector();
    testMyString();
    jointTest();
    return 0;
}

void testMyMathVector() {
    cout << "空向量测试" << endl;
    run(MyMathVector empty_vector(new int[0]{}, 0))
    my_assert(empty_vector, "()")

    cout << "浮点数测试" << endl;
    run(MyMathVector double_vector_1(new double[3]{0.1, 2.2, 3.3}, 3))
    run(MyMathVector double_vector_2(new double[3]{0.2, 2.2, 3.3}, 3))
    // 由于浮点数的精度问题，对于浮点数的加法，只要保证精度在0.000001以内即可
    my_assert(double_vector_1 + double_vector_2, *(new MyMathVector(new double[3]{0.2999995, 4.4, 6.6}, 3)))

    MyMathVector v1(new int[3]{1, 2, 3}, 3);
    MyMathVector v2(new int[3]{4, 5, 6}, 3);
    cout << "输出测试" << endl;
    my_assert(v1, "(1, 2, 3)")
    my_assert(v2, "(4, 5, 6)")
    cout << "加减法测试" << endl;
    my_assert(v1 + v2, "(5, 7, 9)")
    my_assert(v1 - v2, "(-3, -3, -3)")
    cout << "数乘测试" << endl;
    my_assert(v1 * 2, "(2, 4, 6)")
    cout << "下标访问[]测试" << endl;
    my_assert(static_cast<int>(v1[1]), 2)
    cout << "下标赋值[]测试" << endl;
    run(v1[1] = 10)
    my_assert(v1, "(1, 10, 3)")
    cout << "叉乘测试" << endl;
    my_assert(v1, "(1, 10, 3)")
    my_assert(v2, "(4, 5, 6)")
    my_assert(v1.cross(v2), "(45, 6, -35)")
    my_assert(v2.cross(v1), -v1.cross(v2))
    cout << "向量拷贝测试" << endl;
    run(MyMathVector v3(v1))
    my_assert(v3, "(1, 10, 3)")
    cout << "向量移动测试" << endl;
    run(MyMathVector v4(std::move(v3)))
    my_assert(v4, "(1, 10, 3)")
    cout << "向量赋值测试" << endl;
    run(v3 = v4)
    my_assert(v3, "(1, 10, 3)")
    cout << "向量自赋值测试" << endl;
    run(v3 = v3)
    my_assert(v3, "(1, 10, 3)")
    cout << "向量加减赋值测试" << endl;
    run(v3 += v4)
    my_assert(v3, "(2, 20, 6)")
    run(v3 -= v4)
    my_assert(v3, "(1, 10, 3)")
    cout << "向量数乘赋值测试" << endl;
    run(v3 *= 2)
    my_assert(v3, "(2, 20, 6)")
    cout << "向量比较测试" << endl;
    my_assert(v1, "(1, 10, 3)")
    my_assert(v2, "(4, 5, 6)")
    my_assert(v1 == v2, false)
    my_assert(v1 != v2, true)
    cout << "向量缩放测试" << endl;
    my_assert(v1.getSize(), 3)
    run(v1.resize(5))
    my_assert(v1, "(1, 10, 3, 0, 0)")
    my_assert(v1.getSize(), 5)
    run(v1.resize(2))
    my_assert(v1, "(1, 10)")
    my_assert(v1.getSize(), 2)
    run(v1.resize(3))
    my_assert(v1, "(1, 10, 0)")
    my_assert(v1.getSize(), 3)
    run(v1.resize(0))
    my_assert(v1, "()")
    my_assert(v1.getSize(), 0)


    cout << "=======================================" << endl;
    cout << "输入测试" << endl;
    run(v1.resize(2))
    run(istringstream is("2 3"))
    run(is >> v1)
    my_assert(v1, "(2, 3)")
    cout << "异常测试" << endl;
    my_assert(v1, "(2, 3)")
    my_assert(v2, "(4, 5, 6)")
    my_assert_throws(v1.resize(-1), invalid_argument)
    my_assert_throws(v1 + v2, invalid_argument)
    my_assert_throws(v1 - v2, invalid_argument)
    my_assert_throws(v1[3], out_of_range)

}

void testMyString() {
    cout << "默认构造函数测试" << endl;
    run(MyString default_construct = MyString())
    my_assert(default_construct, "")
    my_assert(default_construct.getSize(), 0)
    cout << "空指针测试" << endl;
    run(MyString nullptrString(nullptr, 0))
    my_assert(nullptrString, "")
    my_assert(nullptrString.getSize(), 0)
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
    my_assert(static_cast<char>(biggerString[0]), 'a')
    cout << "下标访问异常测试" << endl;
    my_assert_throws(biggerString[3], std::out_of_range)
}

void jointTest() {
    run(MyString v1("Hello"))
    run(MyMathVector v2(new char[]{'1', '2', '3'}, 3))
    run(MyMathVector v3(new char[]{'4', '5', '6'}, 3))
    run(MyVector<char> *v)

    cout << "MyString 的多态测试" << endl;
    run(v = &v1)
    my_assert(v->toString(), "Hello")
    run(v->append(v3))
    my_assert(v->toString(), "Hello456")
    my_assert(static_cast<char>((*v)[0]), 'H')
    run(v->clear())
    my_assert(v->toString(), "")

    cout << "MyMathVector 的多态测试" << endl;
    run(v = &v2)
    my_assert(v->toString(), "(1, 2, 3)")
    run(v->append(v3))
    my_assert(v->toString(), "(1, 2, 3, 4, 5, 6)")
    my_assert(static_cast<int>((*v)[0]), '1')
    run(v->clear())
    my_assert(v->toString(), "()")
}
