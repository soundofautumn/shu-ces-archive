//
// Created by 邱姜铭 on 2023/11/20.
//

#ifndef PLANECLASS_POLYGON_H
#define PLANECLASS_POLYGON_H

#include "Shape2D.h"

class Polygon : public Shape2D {
public:
    Polygon();

    Polygon(const Point2D *points, int size);

    Polygon(const Polygon &generalPolygon);

    Polygon(const Polygon *generalPolygon);

    ~Polygon();

    std::ostream &print(std::ostream &os) const override;

    std::istream &read(std::istream &is) override;

    Point2D getGravityCenter() const override;

    value_type getPerimeter() const;

    value_type getArea() const;

};


#endif //PLANECLASS_POLYGON_H
