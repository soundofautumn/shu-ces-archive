#include <iostream>
#include "Point2D.h"
#include "Shape2D.h"
#include "Line.h"
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Polygon.h"

using namespace std;


/**
 * 设计描述二维点的类Point2D和二维几何图形的类Shape2D。功能要求：

    1、重载输入输出流运算符，实现类对象的输入输出；

    2、Point2D类除了具有基本的构造、拷贝构造、析构和赋值函数之外，还应具有以下功能：

        2.1获取当前点的坐标；

        2.2设置当前点的坐标；

        2.3计算模长；

        2.4计算方向向量；

        2.5 计算两点间的距离；

    3、以Shape2D类为基类派生四个子类，分别表示直线段、圆、三角形、矩形和一般多边形四种图形。基类中的数据成员为一组二维点和点的个数，子类没有新增的数据成员。各类均具有基本的构造、拷贝构造、析构和赋值函数。其他功能要求如下：

        3.1当对象为直线段时，能够计算直线段长度和斜率；

        3.2当对象是圆时，能够计算半径、周长和面积；

        3.3当对象是三角形时，计算周长和面积；

        3.4当对象是矩形时，计算长宽比和面积；

        3.5当对象是一般多边形时，计算周长和面积；

        3.6计算二维图形的重心坐标。

    4、编写测试函数，测试所有功能。

    5、程序具有良好的可交互性。
 */

void test();

int main() {
    test();
    return 0;
}

void test() {
    Point2D p1, p2;
    cout << "Please input two points: " << endl;
    cin >> p1 >> p2;
    cout << "p1 direction vector:"
         << p1.getDirectionVector() << endl;
    cout << "p2 direction vector:"
         << p2.getDirectionVector() << endl;
    cout << "p1 distance to p2:"
         << p1.getDistance(p2) << endl;
    cout << "p2 distance to p1:"
         << p2.getDistance(p1) << endl;
    cout << "p1 mod length:"
         << p1.getModLength() << endl;
    cout << "p2 mod length:"
         << p2.getModLength() << endl;

    cout << "====================================" << endl;

    Line line1;
    cin >> line1;

    cout << "line1 length:"
         << line1.getLength() << endl;
    cout << "line1 slope:"
         << line1.getSlope() << endl;

    Circle circle1;
    cin >> circle1;

    cout << "circle1 radius:"
         << circle1.getRadius() << endl;
    cout << "circle1 area:"
         << circle1.getArea() << endl;
    cout << "circle1 perimeter:"
         << circle1.getPerimeter() << endl;

    Triangle triangle1;
    cin >> triangle1;

    cout << "triangle1 perimeter:"
         << triangle1.getPerimeter() << endl;
    cout << "triangle1 area:"
         << triangle1.getArea() << endl;

    Rectangle rectangle1;
    cin >> rectangle1;


    cout << "rectangle1 area:"
         << rectangle1.getArea() << endl;
    cout << "rectangle1 ratio:"
         << rectangle1.getRatio() << endl;

    Polygon polygon1;
    cin >> polygon1;

    cout << "polygon1 area:"
         << polygon1.getArea() << endl;
    cout << "polygon1 perimeter:"
         << polygon1.getPerimeter() << endl;

    cout << "====================================" << endl;

    cout << "Shape2D test:" << endl;

    Shape2D *shape2D;

    shape2D = &line1;
    cout << "line1 gravity center:"
         << shape2D->getGravityCenter() << endl;
    shape2D = &circle1;
    cout << "circle1 gravity center:"
         << shape2D->getGravityCenter() << endl;
    shape2D = &triangle1;
    cout << "triangle1 gravity center:"
         << shape2D->getGravityCenter() << endl;
    shape2D = &rectangle1;
    cout << "rectangle1 gravity center:"
         << shape2D->getGravityCenter() << endl;
    shape2D = &polygon1;
    cout << "polygon1 gravity center:"
         << shape2D->getGravityCenter() << endl;
}
