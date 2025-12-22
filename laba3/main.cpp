#include <iostream>
#include <sstream>
#include "include/point.h"
#include "include/figure.h"
#include "include/trapezoid.h"
#include "include/diamond.h"
#include "include/pentagon.h"
#include "include/figures.h"

static void printFigureInfo(const char* name, const Figure& f) {
    std::cout << name << '\n' << f;
    Point c = f.calcGeometricCenter();
    std::cout << "Geometric center:" << c << "\n";
    std::cout << "S: " << static_cast<double>(f) << "\n\n";
}

int main() {
    Trapezoid t({ {0,0}, {4,0}, {3,2}, {1,2} });
    Diamond d({ {0,0}, {2,2}, {4,0}, {2,-2} });
    Pentagon p({ {0,1}, {0.951,0.309}, {0.588,-0.809},
                   {-0.588,-0.809}, {-0.951,0.309} });

    printFigureInfo("Trapezoid t1", t);
    printFigureInfo("Diamond d1", d);
    printFigureInfo("Pentagon p1", p);

    std::istringstream inTrap("0 0 4 0 3 2 1 2");
    Trapezoid t_in;
    inTrap >> t_in;
    printFigureInfo("Trapezoid t_in (Read >>)", t_in);

    Trapezoid t_copy = t;
    std::cout << "t == t_copy ? " << (t == t_copy ? "true" : "false") << "\n";

    Diamond d_move = std::move(d);
    std::cout << "Moved diamond area: " << static_cast<double>(d_move) << "\n\n";

    Figure* fA = new Trapezoid(t);
    Figure* fB = new Diamond(d_move);
    Figure* fC = new Pentagon(p);

    Figures figs({ fA, fB, fC });

    std::cout << "== Geometric centers for each figure ==\n";
    figs.printCenterForEachFigure();

    std::cout << "\n== S for each figure ==\n";
    figs.printAreaForEachFigure();

    std::cout << "\n== Geometric center and S for each figures ==\n";
    figs.printCenterAndAreaForEachFigure();

    double total = figs.calcTotalArea();
    std::cout << "\nFull S for deleting: " << total << "\n";

    std::cout << "Size before removal: " << figs.getSize() << "\n";
    figs.deleteFigure(1);
    std::cout << "Size after removal: " << figs.getSize() << "\n";

    double total_after = figs.calcTotalArea();
    std::cout << "Total area after removal: " << total_after << "\n";
    
    return 0;
}
