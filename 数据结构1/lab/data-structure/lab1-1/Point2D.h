//
// Created by 邱姜铭 on 2023/11/20.
//

#ifndef PLANECLASS_POINT2D_H
#define PLANECLASS_POINT2D_H

#include <iostream>

/**
 * Point2D类除了具有基本的构造、拷贝构造、析构和赋值函数之外，还应具有以下功能：

        2.1获取当前点的坐标；

        2.2设置当前点的坐标；

        2.3计算模长；

        2.4计算方向向量；

        2.5 计算两点间的距离；
 */
class Point2D {
private:
    typedef double value_type;
    static_assert(std::is_floating_point<value_type>::value, "value_type must be floating point");
    value_type x, y;
public:
    Point2D();

    Point2D(value_type x, value_type y);

    Point2D(const Point2D &point2D);

    explicit Point2D(const Point2D *point2D);

    ~Point2D();

    Point2D &operator=(const Point2D &point2D);

    Point2D &operator=(const Point2D *point2D);

    Point2D operator+(const Point2D &point2D) const;

    Point2D operator-(const Point2D &point2D) const;

    bool operator==(const Point2D &point2D) const;

    bool operator!=(const Point2D &point2D) const;

    friend std::ostream &operator<<(std::ostream &os, const Point2D &point2D);

    friend std::istream &operator>>(std::istream &is, Point2D &point2D);

    value_type getX() const;

    value_type getY() const;

    void setX(value_type x);

    void setY(value_type y);

    value_type getModLength() const;

    Point2D getDirectionVector() const;

    value_type getDistance(const Point2D &point2D) const;

};


#endif //PLANECLASS_POINT2D_H
