#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"
#include <cmath>

template<typename T>
class Rhombus : public Figure<T> {
public:
    Rhombus() { create(Point<T>(0, 0), 2, 2); }
    Rhombus(const Point<T>& center, T horizontal, T vertical) { create(center, horizontal, vertical); }

    Point<T> center() const override {
        T x_sum = 0;
        T y_sum = 0;
        for (const auto& point : this->points) {
            x_sum += point->x();
            y_sum += point->y();
        }
        return Point<T>(x_sum / 4, y_sum / 4);
    }

    double area() const override {
        T diagonal1 = std::sqrt(
            std::pow(this->points[0]->x() - this->points[2]->x(), 2) +
            std::pow(this->points[0]->y() - this->points[2]->y(), 2)
        );
        T diagonal2 = std::sqrt(
            std::pow(this->points[1]->x() - this->points[3]->x(), 2) +
            std::pow(this->points[1]->y() - this->points[3]->y(), 2)
        );
        return (static_cast<double>(diagonal1) * static_cast<double>(diagonal2)) / 2.0;
    }

    void print(std::ostream& os) const override {
        os << "Rhombus: ";
        for (const auto& point : this->points) {
            os << "(" << point->x() << "," << point->y() << ") ";
        }
    }

    void read(std::istream& is) override {
        T x, y, d1, d2;
        std::cout << "Enter rhombus center and diagonals (x y horizontal_diagonal vertical_diagonal): ";
        is >> x >> y >> d1 >> d2;
        create(Point<T>(x, y), d1, d2);
    }

    bool equals(const Figure<T>& other) const override {
        const Rhombus* other_rhombus = dynamic_cast<const Rhombus*>(&other);
        if (!other_rhombus) return false;
        return this->points.size() == other_rhombus->points.size();
    }

private:
    void create(const Point<T>& center, T horizontal, T vertical) {
        this->points.clear();
        T half_h = horizontal / 2;
        T half_v = vertical / 2;

        this->points.push_back(std::make_unique<Point<T>>(center.x(), center.y() + half_v));
        this->points.push_back(std::make_unique<Point<T>>(center.x() + half_h, center.y()));
        this->points.push_back(std::make_unique<Point<T>>(center.x(), center.y() - half_v));
        this->points.push_back(std::make_unique<Point<T>>(center.x() - half_h, center.y()));
    }
};

#endif