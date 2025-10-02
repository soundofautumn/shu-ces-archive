//
// Created by 邱姜铭 on 2023/11/20.
//

#include "Point2D.h"
#include <cmath>

Point2D::Point2D() : x(0), y(0) {}

Point2D::Point2D(value_type x, value_type y) : x(x), y(y) {}

Point2D::Point2D(const Point2D &point2D) = default;

Point2D::Point2D(const Point2D *point2D) : x(point2D->x), y(point2D->y) {}

Point2D::~Point2D() = default;

Point2D &Point2D::operator=(const Point2D &point) {
    if (this != &point) {
        x = point.x;
        y = point.y;
    }
    return *this;
}

Point2D &Point2D::operator=(const Point2D *point) {
    if (this != point) {
        x = point->x;
        y = point->y;
    }
    return *this;
}

Point2D Point2D::operator+(const Point2D &point) const {
    return {x + point.x, y + point.y};
}

Point2D Point2D::operator-(const Point2D &point) const {
    return {x - point.x, y - point.y};
}

std::ostream &operator<<(std::ostream &os, const Point2D &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

std::istream &operator>>(std::istream &is, Point2D &point) {
    is >> point.x >> point.y;
    return is;
}

bool Point2D::operator==(const Point2D &point) const {
    return x == point.x && y == point.y;
}

bool Point2D::operator!=(const Point2D &point) const {
    return x != point.x || y != point.y;
}

Point2D::value_type Point2D::getX() const {
    return x;
}

Point2D::value_type Point2D::getY() const {
    return y;
}

void Point2D::setX(Point2D::value_type new_x) {
    this->x = new_x;
}

void Point2D::setY(Point2D::value_type new_y) {
    this->y = new_y;
}

Point2D::value_type Point2D::getModLength() const {
    return sqrt(x * x + y * y);
}

Point2D Point2D::getDirectionVector() const {
    return {x / getModLength(), y / getModLength()};
}

Point2D::value_type Point2D::getDistance(const Point2D &point) const {
    return sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
}


