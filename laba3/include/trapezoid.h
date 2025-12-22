#pragma once

#include "figure.h"
#include "point.h"
#include <initializer_list>

class Trapezoid : public Figure {
  public:
    Trapezoid();
    Trapezoid(const std::initializer_list<Point> &t);
    Trapezoid(const Trapezoid &);
    Trapezoid(Trapezoid &&);
    Trapezoid &operator=(const Trapezoid &);
    Trapezoid &operator=(Trapezoid &&);
    bool operator==(const Trapezoid &other) const;

    static constexpr int numOfPoints = 4;

    int getNumOfPoints() const override { return numOfPoints; }
};