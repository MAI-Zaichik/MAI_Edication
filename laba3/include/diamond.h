#pragma once

#include "figure.h"
#include "point.h"
#include <initializer_list>

class Diamond : public Figure {
  public:
    Diamond();
    Diamond(const std::initializer_list<Point> &t);
    Diamond(const Diamond &other);
    Diamond(Diamond &&other);
    Diamond &operator=(const Diamond &);
    Diamond &operator=(Diamond &&);
    bool operator==(const Diamond &other) const;

    static constexpr int numOfPoints = 4;

    int getNumOfPoints() const override { return numOfPoints; }
};