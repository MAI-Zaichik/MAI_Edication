#include "../include/figures.h"
#include <iostream>
#include <vector>

Figures::Figures(const size_t &n) {
    array.resize(n);
}
Figures::Figures(const std::initializer_list<Figure *> &t) {
    array.assign(t);
}

void Figures::printCenterForEachFigure() {
    for (Figure* fig : array) {
        std::cout << *fig << "Геометрический центр: " << fig->calcGeometricCenter() << "\n\n";
    }
}

void Figures::printAreaForEachFigure() {
    for (Figure* fig : array) {
        std::cout << *fig << "Площадь фигуры: " << fig->calcArea() << "\n\n";
    }
}

void Figures::printCenterAndAreaForEachFigure() {
    for (Figure* fig : array) {
        std::cout << *fig << "Геометрический центр: " << fig->calcGeometricCenter() << '\n';
        std::cout << "Площадь фигуры: " << fig->calcArea() << "\n\n";
    }
}

double Figures::calcTotalArea() {
    double s = 0;
    for (Figure* fig : array) {
        s += fig->calcArea();
    }
    return s;
}

void Figures::deleteFigure(int index) {
    array.erase(array.begin() + index);
}

size_t Figures::getSize() const { return array.size(); }