//
// Created by 邱姜铭 on 2023/11/20.
//

#ifndef PLANECLASS_RECTANGLE_H
#define PLANECLASS_RECTANGLE_H

#include "Shape2D.h"

class Rectangle : public Shape2D {

public:
    Rectangle();

    Rectangle(const Point2D &point1, const Point2D &point2);

    Rectangle(const Rectangle &rectangle);

    Rectangle(const Rectangle *rectangle);

    ~Rectangle();

    std::ostream &print(std::ostream &os) const override;

    std::istream &read(std::istream &is) override;

    Point2D getGravityCenter() const override;

    //计算长宽比
    value_type getRatio() const;

    //计算面积
    value_type getArea() const;

};


#endif //PLANECLASS_RECTANGLE_H
