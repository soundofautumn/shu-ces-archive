//
// Created by 邱姜铭 on 2023/11/20.
//

#ifndef PLANECLASS_CIRCLE_H
#define PLANECLASS_CIRCLE_H

#include "Shape2D.h"

class Circle : public Shape2D {

public:
    Circle();

    Circle(const Point2D &center, value_type radius);

    Circle(const Point2D &center, const Point2D &point);

    Circle(const Circle &circle);

    Circle(const Circle *circle);

    ~Circle();

    std::ostream &print(std::ostream &os) const override;

    std::istream &read(std::istream &is) override;

    Point2D getGravityCenter() const override;

    value_type getRadius() const;

    value_type getPerimeter() const;

    value_type getArea() const;
};


#endif //PLANECLASS_CIRCLE_H
