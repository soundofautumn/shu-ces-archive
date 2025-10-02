//
// Created by 邱姜铭 on 2023/11/20.
//

#ifndef PLANECLASS_LINE_H
#define PLANECLASS_LINE_H

#include "Shape2D.h"

class Line : public Shape2D {
public:
    Line();

    Line(const Point2D& begin, const Point2D& end);

    Line(const Line &line);

    explicit Line(const Line *line);

    ~Line() override;

    std::ostream &print(std::ostream &os) const override;

    std::istream &read(std::istream &is) override;

    Point2D getGravityCenter() const override;

    value_type getLength() const;

    value_type getSlope() const;
};


#endif //PLANECLASS_LINE_H
