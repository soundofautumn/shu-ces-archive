//
// Created by 邱姜铭 on 2023/11/20.
//

#include <cmath>
#include "Circle.h"

#define PI 3.14159265358979323846

Circle::Circle() : Shape2D() {
    this->points = new Point2D[2];
    this->point_num = 2;
    this->points[0] = {0, 0};
    this->points[1] = {0, 0};
}

Circle::Circle(const Point2D &center, value_type radius) : Circle(center,
                                                                  Point2D(center.getX() + radius, center.getY())) {
}

Circle::Circle(const Point2D &center, const Point2D &point) : Shape2D() {
    this->points = new Point2D[2];
    this->point_num = 2;
    this->points[0] = center;
    this->points[1] = point;
}

Circle::Circle(const Circle &circle) = default;

Circle::Circle(const Circle *circle) : Shape2D(circle) {}

Circle::~Circle() = default;

std::ostream &Circle::print(std::ostream &os) const {
    os << "Circle: " << std::endl;
    for (int i = 0; i < this->point_num; ++i) {
        os << this->points[i] << std::endl;
    }
    return os;
}

std::istream &Circle::read(std::istream &is) {
    std::cout << "Please input the center point and a point on the circle: " << std::endl;
    is >> this->points[0] >> this->points[1];
    return is;
}

Point2D Circle::getGravityCenter() const {
    return this->points[0];
}

Circle::value_type Circle::getRadius() const {
    return sqrt(pow(this->points[0].getX() - this->points[1].getX(), 2) +
                pow(this->points[0].getY() - this->points[1].getY(), 2));
}

Circle::value_type Circle::getPerimeter() const {
    return 2 * PI * this->getRadius();
}

Circle::value_type Circle::getArea() const {
    return PI * pow(this->getRadius(), 2);
}




