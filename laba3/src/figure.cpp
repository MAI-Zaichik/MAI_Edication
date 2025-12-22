#include "../include/figure.h"

Figure::Figure(int numOfPoints) { points.resize(numOfPoints); }

Figure::Figure(const std::initializer_list<Point> &t) { points.assign(t); }

std::ostream &operator<<(std::ostream &os, const Figure &figure) {
    os << "Точки фигуры:\n";
    for (int i = 0; i < figure.points.size(); i++) {
        os << figure.points[i] << ' ';
    }
    os << '\n';
    return os;
}

Figure::operator double() const { return calcArea(); }

double Figure::calcArea() const { return std::abs(calcAreaSigned()); }

double Figure::calcAreaSigned() const {
    double s = 0;
    for (int i = 0; i < points.size(); i++) {
        int j = (i + 1) % points.size();
        s += points[i][0] * points[j][1] - points[j][0] * points[i][1];
    }

    return s / 2;
}

Point Figure::calcGeometricCenter() const {
    double a = calcAreaSigned();
    double cx = 0, cy = 0;
    for (int i = 0; i < points.size(); i++) {
        int j = (i + 1) % points.size();
        double cross =
            points[i][0] * points[j][1] - points[j][0] * points[i][1];
        cx += (points[i][0] + points[j][0]) * cross;
        cy += (points[i][1] + points[j][1]) * cross;
    }
    cx /= (6 * a);
    cy /= (6 * a);
    return Point(cx, cy);
}

std::istream &operator>>(std::istream &is, Figure &figure) {
    return figure.read(is);
}

bool Figure::operator==(const Figure &other) const {
    return points == other.points;
}

std::istream &Figure::readPoints(std::istream &is, int pointNum) {
    points.resize(pointNum);
    for (int i = 0; i < pointNum; i++) {
        is >> points[i];
    }
    return is;
}

std::istream &Figure::read(std::istream &is) {
    return readPoints(is, getNumOfPoints());
}