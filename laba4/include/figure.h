#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <memory>
#include <vector>
#include <iostream>
#include <type_traits>

template<typename T>
class Figure {
    static_assert(std::is_scalar_v<T>, "T must be scalar type");
protected:
    std::vector<std::unique_ptr<Point<T>>> points;

public:
    virtual ~Figure() = default;

    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    // Чисто виртуальный метод для сравнения
    virtual bool equals(const Figure& other) const = 0;
    
    // Не предоставляем оператор == в базовом классе
    operator double() const { return area(); }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.print(os);
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Figure<T>& fig) {
    fig.read(is);
    return is;
}

#endif