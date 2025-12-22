#pragma once

#include "point.h"
#include <initializer_list>
#include <iostream>
#include <vector>

class Figure {
  protected:
    Figure() = default;
    Figure(int numOfPoints);
    Figure(const std::initializer_list<Point> &t);
    Figure(const Figure &other) = default;
    Figure(Figure &&other) noexcept = default;
    Figure &operator=(const Figure &other) = default;
    Figure &operator=(Figure &&other) = default;

    std::istream& read(std::istream &is);

    std::istream& readPoints(std::istream &is, int pointNum);
  public:
    bool operator==(const Figure &other) const;

    Point calcGeometricCenter() const;
    double calcArea() const;
    double calcAreaSigned() const;
    explicit operator double() const;

    friend std::ostream &operator<<(std::ostream &os, const Figure &figure);
    friend std::istream &operator>>(std::istream &is, Figure &figure);

    virtual int getNumOfPoints() const = 0;
    
    virtual ~Figure() = default;
  private:
    std::vector<Point> points;
};