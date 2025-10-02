//
// Created by 邱姜铭 on 2023/11/20.
//

#include <cmath>
#include "Rectangle.h"

Rectangle::Rectangle() : Shape2D() {
    this->points = new Point2D[2];
    this->point_num = 2;
    this->points[0] = {0, 0};
    this->points[1] = {0, 0};
}

Rectangle::Rectangle(const Point2D &point1, const Point2D &point2) : Shape2D() {
    this->points = new Point2D[2];
    this->point_num = 2;
    this->points[0] = point1;
    this->points[1] = point2;
}

Rectangle::Rectangle(const Rectangle &rectangle) = default;

Rectangle::Rectangle(const Rectangle *rectangle) : Shape2D(rectangle) {}

Rectangle::~Rectangle() = default;

std::ostream &Rectangle::print(std::ostream &os) const {
    os << "Rectangle: " << std::endl;
    for (int i = 0; i < this->point_num; ++i) {
        os << this->points[i] << std::endl;
    }
    return os;
}

std::istream &Rectangle::read(std::istream &is) {
    std::cout << "Please input two points of the rectangle: " << std::endl;
    is >> this->points[0] >> this->points[1];
    return is;
}

Point2D Rectangle::getGravityCenter() const {
    return {(this->points[0].getX() + this->points[1].getX()) / 2,
            (this->points[0].getY() + this->points[1].getY()) / 2};
}

Rectangle::value_type Rectangle::getRatio() const {
    return fabs(this->points[0].getX() - this->points[1].getX()) /
           fabs(this->points[0].getY() - this->points[1].getY());
}

Rectangle::value_type Rectangle::getArea() const {
    return fabs(this->points[0].getX() - this->points[1].getX()) *
           fabs(this->points[0].getY() - this->points[1].getY());
}


