//
// Created by 邱姜铭 on 2023/11/20.
//

#include <cmath>
#include "Polygon.h"

Polygon::Polygon() : Shape2D() {}

Polygon::Polygon(const Point2D *points, int size) : Shape2D(points, size) {}

Polygon::Polygon(const Polygon &generalPolygon) = default;

Polygon::Polygon(const Polygon *generalPolygon) : Shape2D(generalPolygon) {}

Polygon::~Polygon() = default;

std::ostream &Polygon::print(std::ostream &os) const {
    os << "Polygon: " << std::endl;
    for (int i = 0; i < this->point_num; ++i) {
        os << this->points[i] << std::endl;
    }
    return os;
}

std::istream &Polygon::read(std::istream &is) {
    std::cout << "Please input the number of points of the general polygon: " << std::endl;
    is >> this->point_num;
    delete[] this->points;
    this->points = new Point2D[this->point_num];
    std::cout << "Please input the points of the general polygon: " << std::endl;
    for (int i = 0; i < this->point_num; ++i) {
        is >> this->points[i];
    }
    return is;
}

Point2D Polygon::getGravityCenter() const {
    value_type x = 0, y = 0;
    for (int i = 0; i < this->point_num; ++i) {
        x += this->points[i].getX();
        y += this->points[i].getY();
    }
    return {x / this->point_num, y / this->point_num};
}

Polygon::value_type Polygon::getPerimeter() const {
    value_type perimeter = 0;
    for (int i = 0; i < this->point_num; ++i) {
        perimeter += sqrt(pow(this->points[i].getX() - this->points[(i + 1) % this->point_num].getX(), 2) +
                          pow(this->points[i].getY() - this->points[(i + 1) % this->point_num].getY(), 2));
    }
    return perimeter;
}

Polygon::value_type Polygon::getArea() const {
    value_type area = 0;
    for (int i = 0; i < this->point_num; ++i) {
        area += this->points[i].getX() * this->points[(i + 1) % this->point_num].getY() -
                this->points[i].getY() * this->points[(i + 1) % this->point_num].getX();
    }
    return fabs(area) / 2;
}


