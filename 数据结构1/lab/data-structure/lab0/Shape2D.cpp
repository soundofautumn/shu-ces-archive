//
// Created by 邱姜铭 on 2023/11/20.
//

#include "Shape2D.h"

Shape2D::Shape2D() : points(nullptr), point_num(0) {}

Shape2D::Shape2D(const Point2D *points, int point_num) : points(nullptr), point_num(0) {
    this->points = new Point2D[point_num];
    this->point_num = point_num;
    for (int i = 0; i < point_num; ++i) {
        this->points[i] = points[i];
    }
}

Shape2D::Shape2D(const Shape2D &shape2D) : points(nullptr), point_num(0) {
    this->points = new Point2D[shape2D.point_num];
    this->point_num = shape2D.point_num;
    for (int i = 0; i < shape2D.point_num; ++i) {
        this->points[i] = shape2D.points[i];
    }
}

Shape2D::Shape2D(const Shape2D *shape2D) : points(nullptr), point_num(0) {
    this->points = new Point2D[shape2D->point_num];
    this->point_num = shape2D->point_num;
    for (int i = 0; i < shape2D->point_num; ++i) {
        this->points[i] = shape2D->points[i];
    }
}

Shape2D::~Shape2D() {
    delete[] this->points;
}

Shape2D &Shape2D::operator=(const Shape2D &shape2D) {
    if (&shape2D == this) {
        return *this;
    }
    delete[] this->points;
    this->points = new Point2D[shape2D.point_num];
    this->point_num = shape2D.point_num;
    for (int i = 0; i < shape2D.point_num; ++i) {
        this->points[i] = shape2D.points[i];
    }
    return *this;
}

Shape2D &Shape2D::operator=(const Shape2D *shape2D) {
    if (shape2D == this) {
        return *this;
    }
    delete[] this->points;
    this->points = new Point2D[shape2D->point_num];
    this->point_num = shape2D->point_num;
    for (int i = 0; i < shape2D->point_num; ++i) {
        this->points[i] = shape2D->points[i];
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Shape2D &shape2D) {
    return shape2D.print(os);
}

std::istream &operator>>(std::istream &is, Shape2D &shape2D) {
    return shape2D.read(is);
}

