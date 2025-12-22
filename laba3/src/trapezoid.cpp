#include "../include/trapezoid.h"
#include <initializer_list>
#include "../include/point.h"

Trapezoid::Trapezoid() : Figure(numOfPoints) {}

Trapezoid::Trapezoid(const std::initializer_list<Point> &t) : Figure(t) {}

Trapezoid::Trapezoid(const Trapezoid &other) : Figure(other) {}
Trapezoid::Trapezoid(Trapezoid &&other) : Figure(other) {}

Trapezoid &Trapezoid::operator=(const Trapezoid &other) {
    Figure::operator=(other);
    return *this;
}

Trapezoid &Trapezoid::operator=(Trapezoid &&other) {
    Figure::operator=(other);
    return *this;
}


bool Trapezoid::operator==(const Trapezoid &other) const {
    return Figure::operator==(other);
}