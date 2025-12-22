#include "../include/diamond.h"
#include <initializer_list>
#include "../include/point.h"

Diamond::Diamond() : Figure(numOfPoints) {}

Diamond::Diamond(const std::initializer_list<Point> &t) : Figure(t) {}

Diamond::Diamond(const Diamond &other) : Figure(other) {}
Diamond::Diamond(Diamond &&other) : Figure(other) {}

Diamond &Diamond::operator=(const Diamond &other) {
    Figure::operator=(other);
    return *this;
}

Diamond &Diamond::operator=(Diamond &&other) {
    Figure::operator=(other);
    return *this;
}

bool Diamond::operator==(const Diamond &other) const {
    return Figure::operator==(other);
}