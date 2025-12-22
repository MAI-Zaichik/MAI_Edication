#ifndef HEXAGON_H
#define HEXAGON_H

#include "figure.h"
#include <cmath>

template<typename T>
class Hexagon : public Figure<T> {
public:
    Hexagon() { create(Point<T>(0, 0), 1); }
    Hexagon(const Point<T>& center, T radius) { create(center, radius); }

    Point<T> center() const override {
        T x_sum = 0;
        T y_sum = 0;
        for (const auto& point : this->points) {
            x_sum += point->x();
            y_sum += point->y();
        }
        return Point<T>(x_sum / 6, y_sum / 6);
    }

    double area() const override {
        T side = std::sqrt(std::pow(this->points[0]->x() - this->points[1]->x(), 2) +
                          std::pow(this->points[0]->y() - this->points[1]->y(), 2));
        return (3.0 * std::sqrt(3.0) * side * side) / 2.0;
    }

    void print(std::ostream& os) const override {
        os << "Hexagon: ";
        for (const auto& point : this->points) {
            os << "(" << point->x() << "," << point->y() << ") ";
        }
    }

    void read(std::istream& is) override {
        T x, y, radius;
        std::cout << "Enter hexagon center and radius (x y radius): ";
        is >> x >> y >> radius;
        create(Point<T>(x, y), radius);
    }

    bool equals(const Figure<T>& other) const override {
        const Hexagon* other_hexagon = dynamic_cast<const Hexagon*>(&other);
        if (!other_hexagon) return false;
        return this->points.size() == other_hexagon->points.size();
    }

private:
    void create(const Point<T>& center, T radius) {
        this->points.clear();
        for (int i = 0; i < 6; ++i) {
            double angle = 2 * M_PI * i / 6;
            T x = center.x() + radius * static_cast<T>(std::cos(angle));
            T y = center.y() + radius * static_cast<T>(std::sin(angle));
            this->points.push_back(std::make_unique<Point<T>>(x, y));
        }
    }
};

#endif