//
// Created by 邱姜铭 on 2023/11/20.
//

#include <cmath>
#include "Line.h"

Line::Line() : Shape2D() {
    this->points = new Point2D[2];
    this->point_num = 2;
    this->points[0] = {0, 0};
    this->points[1] = {0, 0};
}

Line::Line(const Point2D &begin, const Point2D &end) : Shape2D() {
    this->points = new Point2D[2];
    this->point_num = 2;
    this->points[0] = begin;
    this->points[1] = end;
}

Line::Line(const Line &line) = default;

Line::Line(const Line *line) : Shape2D(line) {}

Line::~Line() = default;

std::ostream &Line::print(std::ostream &os) const {
    os << "Line: " << std::endl;
    for (int i = 0; i < this->point_num; ++i) {
        os << this->points[i] << std::endl;
    }
    return os;
}

std::istream &Line::read(std::istream &is) {
    std::cout << "Please input the begin point and end point of the line: " << std::endl;
    is >> this->points[0] >> this->points[1];
    return is;
}

Point2D Line::getGravityCenter() const {
    return {(this->points[0].getX() + this->points[1].getX()) / 2,
            (this->points[0].getY() + this->points[1].getY()) / 2};
}

Line::value_type Line::getLength() const {
    return sqrt(pow(this->points[0].getX() - this->points[1].getX(), 2) +
                pow(this->points[0].getY() - this->points[1].getY(), 2));
}

Line::value_type Line::getSlope() const {
    return (this->points[0].getY() - this->points[1].getY()) / (this->points[0].getX() - this->points[1].getX());
}

