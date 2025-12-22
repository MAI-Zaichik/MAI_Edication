#pragma once

#include "figure.h"
#include "point.h"
#include <initializer_list>

class Pentagon : public Figure {
  public:
    Pentagon();
    Pentagon(const std::initializer_list<Point> &t);
    Pentagon(const Pentagon &other);
    Pentagon(Pentagon &&other);
    Pentagon &operator=(const Pentagon &other);
    Pentagon &operator=(Pentagon &&other);
    bool operator==(const Pentagon &other) const;

    static constexpr int numOfPoints = 5;

    int getNumOfPoints() const override { return numOfPoints; }
};