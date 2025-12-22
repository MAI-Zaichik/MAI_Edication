#ifndef POINT_H
#define POINT_H

#include <type_traits>

template<typename T>
class Point {
    static_assert(std::is_scalar_v<T>, "T must be scalar type");
private:
    T x_value;
    T y_value;

public:
    Point(T x = T(), T y = T()) : x_value(x), y_value(y) {}

    T x() const { return x_value; }
    T y() const { return y_value; }

    bool operator==(const Point& other) const {
        return x_value == other.x_value && y_value == other.y_value;
    }
};

#endif