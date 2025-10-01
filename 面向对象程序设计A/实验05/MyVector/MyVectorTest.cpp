//
// Created by 邱姜铭 on 2023/9/28.
//
#include <sstream>
#include "MyVector.h"
#include "my_assert.h"

using namespace std;


int main() {
    cout << "空向量测试" << endl;
    run(MyVector<int> empty_vector(0, new int[0]{}))
    my_assert(empty_vector, "()")

    run(MyVector<double> double_vector(3, new double[3]{1.1, 2.2, 3.3}))

    MyVector<int> v1(3, new int[3]{1, 2, 3});
    MyVector<int> v2(3, new int[3]{4, 5, 6});
    cout << "输出测试" << endl;
    my_assert(v1, "(1, 2, 3)")
    my_assert(v2, "(4, 5, 6)")
    cout << "加减法测试" << endl;
    my_assert(v1 + v2, "(5, 7, 9)")
    my_assert(v1 - v2, "(-3, -3, -3)")
    cout << "点乘测试" << endl;
    my_assert(v1 * v2, 32)
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
    run(MyVector<int> v3(v1))
    my_assert(v3, "(1, 10, 3)")
    cout << "向量移动测试" << endl;
    run(MyVector<int> v4(std::move(v3)))
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
    my_assert(v1.getDim(), 3)
    run(v1.resize(5))
    my_assert(v1, "(1, 10, 3, 0, 0)")
    my_assert(v1.getDim(), 5)
    run(v1.resize(2))
    my_assert(v1, "(1, 10)")
    my_assert(v1.getDim(), 2)
    run(v1.resize(3))
    my_assert(v1, "(1, 10, 0)")
    my_assert(v1.getDim(), 3)
    run(v1.resize(0))
    my_assert(v1, "()")
    my_assert(v1.getDim(), 0)


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
    my_assert_throws(v1 * v2, invalid_argument)
    my_assert_throws(v1.cross(v2), invalid_argument)
    my_assert_throws(v1[3], out_of_range)
}
