#pragma once

#include <cassert>
#include <cstddef>
#include <iostream>

class Point {
    public:
        Point();
        Point(double x, double y);

        double& operator[](size_t index);
        double operator[](size_t index) const;

        friend std::istream& operator>>(std::istream& is, Point& p);
        friend std::ostream& operator<<(std::ostream& os, const Point& p);

        bool operator==(const Point &other) const;
    
    private:
        double x;
        double y;
};