#include "../include/pentagon.h"
#include "../include/point.h"
#include <initializer_list>

Pentagon::Pentagon() : Figure(numOfPoints) {}

Pentagon::Pentagon(const std::initializer_list<Point> &t) : Figure(t) {}

Pentagon::Pentagon(const Pentagon &other) : Figure(other) {}
Pentagon::Pentagon(Pentagon &&other) : Figure(other) {}

Pentagon &Pentagon::operator=(const Pentagon &other) {
    Figure::operator=(other);
    return *this;
}

Pentagon &Pentagon::operator=(Pentagon &&other) {
    Figure::operator=(other);
    return *this;
}

bool Pentagon::operator==(const Pentagon &other) const {
    return Figure::operator==(other);
}