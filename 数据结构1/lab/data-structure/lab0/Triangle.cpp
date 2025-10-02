//
// Created by 邱姜铭 on 2023/11/20.
//

#include <cmath>
#include "Triangle.h"

Triangle::Triangle() : Shape2D() {
    this->points = new Point2D[3];
    this->point_num = 3;
    this->points[0] = {0, 0};
    this->points[1] = {0, 0};
    this->points[2] = {0, 0};
}

Triangle::Triangle(const Point2D &point1, const Point2D &point2, const Point2D &point3) : Shape2D() {
    this->points = new Point2D[3];
    this->point_num = 3;
    this->points[0] = point1;
    this->points[1] = point2;
    this->points[2] = point3;
}

Triangle::Triangle(const Triangle &triangle) = default;

Triangle::Triangle(const Triangle *triangle) : Shape2D(triangle) {}

Triangle::~Triangle() = default;

std::ostream &Triangle::print(std::ostream &os) const {
    os << "Triangle: " << std::endl;
    for (int i = 0; i < this->point_num; ++i) {
        os << this->points[i] << std::endl;
    }
    return os;
}

std::istream &Triangle::read(std::istream &is) {
    std::cout << "Please input three points of the triangle: " << std::endl;
    is >> this->points[0] >> this->points[1] >> this->points[2];
    return is;
}

Point2D Triangle::getGravityCenter() const {
    return {(this->points[0].getX() + this->points[1].getX() + this->points[2].getX()) / 3,
            (this->points[0].getY() + this->points[1].getY() + this->points[2].getY()) / 3};
}

Triangle::value_type Triangle::getPerimeter() const {
    return sqrt(pow(this->points[0].getX() - this->points[1].getX(), 2) +
                pow(this->points[0].getY() - this->points[1].getY(), 2)) +
           sqrt(pow(this->points[0].getX() - this->points[2].getX(), 2) +
                pow(this->points[0].getY() - this->points[2].getY(), 2)) +
           sqrt(pow(this->points[1].getX() - this->points[2].getX(), 2) +
                pow(this->points[1].getY() - this->points[2].getY(), 2));
}

Triangle::value_type Triangle::getArea() const {
    value_type p = this->getPerimeter() / 2;
    return sqrt(p * (p - sqrt(pow(this->points[0].getX() - this->points[1].getX(), 2) +
                              pow(this->points[0].getY() - this->points[1].getY(), 2))) *
                (p - sqrt(pow(this->points[0].getX() - this->points[2].getX(), 2) +
                          pow(this->points[0].getY() - this->points[2].getY(), 2))) *
                (p - sqrt(pow(this->points[1].getX() - this->points[2].getX(), 2) +
                          pow(this->points[1].getY() - this->points[2].getY(), 2))));
}



