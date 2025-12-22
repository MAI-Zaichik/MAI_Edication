#pragma once

#include "figure.h"
#include <vector>

class Figures {
  public:
    Figures() = default;
    Figures(const size_t &n);
    Figures(const std::initializer_list<Figure *> &t);

    Figures(const Figures &other) = default;
    Figures(Figures &&other) noexcept = default;
    Figures &operator=(const Figures &other) = default;
    Figures &operator=(Figures &&other) = default;
    virtual ~Figures() noexcept = default;

    void printCenterForEachFigure();

    void printAreaForEachFigure();

    void printCenterAndAreaForEachFigure();

    double calcTotalArea();

    void deleteFigure(int index);
    
    size_t getSize() const;

  private:
    std::vector<Figure *> array;
};