//
// Created by 邱姜铭 on 2023/11/20.
//

#ifndef PLANECLASS_TRIANGLE_H
#define PLANECLASS_TRIANGLE_H

#include "Shape2D.h"

class Triangle : public Shape2D {
public:
    Triangle();

    Triangle(const Point2D &point1, const Point2D &point2, const Point2D &point3);

    Triangle(const Triangle &triangle);

    explicit Triangle(const Triangle *triangle);

    ~Triangle() override;

    std::ostream &print(std::ostream &os) const override;

    std::istream &read(std::istream &is) override;

    Point2D getGravityCenter() const override;

    value_type getPerimeter() const;

    value_type getArea() const;

};


#endif //PLANECLASS_TRIANGLE_H
