//
// Created by 邱姜铭 on 2023/11/20.
//

#ifndef PLANECLASS_SHAPE2D_H
#define PLANECLASS_SHAPE2D_H

#include "Point2D.h"

/**
 * 以Shape2D类为基类派生四个子类，分别表示直线段、圆、三角形、矩形和一般多边形四种图形。基类中的数据成员为一组二维点和点的个数，子类没有新增的数据成员。各类均具有基本的构造、拷贝构造、析构和赋值函数。其他功能要求如下：

        3.1当对象为直线段时，能够计算直线段长度和斜率；

        3.2当对象是圆时，能够计算半径、周长和面积；

        3.3当对象是三角形时，计算周长和面积；

        3.4当对象是矩形时，计算长宽比和面积；

        3.5当对象是一般多边形时，计算周长和面积；

        3.6计算二维图形的重心坐标。
 */
class Shape2D {

protected:
    typedef double value_type;
    static_assert(std::is_floating_point<value_type>::value, "value_type must be floating point");
    Point2D *points;
    int point_num;
public:
    Shape2D();

    Shape2D(const Point2D *points, int point_num);

    Shape2D(const Shape2D &shape2D);

    explicit Shape2D(const Shape2D *shape2D);

    virtual ~Shape2D();

    Shape2D &operator=(const Shape2D &shape2D);

    Shape2D &operator=(const Shape2D *shape2D);

    friend std::ostream &operator<<(std::ostream &os, const Shape2D &shape2D);

    friend std::istream &operator>>(std::istream &is, Shape2D &shape2D);

    virtual std::ostream &print(std::ostream &os) const = 0;

    virtual std::istream &read(std::istream &is) = 0;

    virtual Point2D getGravityCenter() const = 0;

};


#endif //PLANECLASS_SHAPE2D_H
