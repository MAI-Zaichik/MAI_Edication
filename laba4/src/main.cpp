#include <iostream>
#include <memory>
#include "../include/array.h"
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"

void displayMenu() {
    std::cout << "\n========== FIGURE MANAGER ==========\n";
    std::cout << "1. Add Rhombus\n";
    std::cout << "2. Add Pentagon\n";
    std::cout << "3. Add Hexagon\n";
    std::cout << "4. Display all figures\n";
    std::cout << "5. Calculate total area\n";
    std::cout << "6. Remove figure\n";
    std::cout << "7. Display figure count\n";
    std::cout << "0. Exit\n";
    std::cout << "===================================\n";
    std::cout << "Choice: ";
}

void addFigure(Array<std::shared_ptr<Figure<double>>>& figures, int type) {
    std::shared_ptr<Figure<double>> figure;
    
    switch(type) {
        case 1:
            figure = std::make_shared<Rhombus<double>>();
            break;
        case 2:
            figure = std::make_shared<Pentagon<double>>();
            break;
        case 3:
            figure = std::make_shared<Hexagon<double>>();
            break;
        default:
            std::cout << "Invalid figure type!\n";
            return;
    }
    
    std::cout << "\n--- Adding new figure ---\n";
    std::cin >> *figure;
    figures.add(figure);
    std::cout << "Figure added successfully!\n";
}

void displayAll(const Array<std::shared_ptr<Figure<double>>>& figures) {
    if (figures.empty()) {
        std::cout << "No figures available.\n";
        return;
    }
    
    std::cout << "\n--- All Figures ---\n";
    for (size_t i = 0; i < figures.size(); i++) {
        std::cout << "[" << i << "] ";
        std::cout << *figures[i] << std::endl;
        Point<double> center = figures[i]->center();
        std::cout << "  Center: (" << center.x() << ", " << center.y() << ")\n";
        std::cout << "  Area: " << figures[i]->area() << "\n";
        std::cout << "  --------------------\n";
    }
}

void calculateTotalArea(const Array<std::shared_ptr<Figure<double>>>& figures) {
    if (figures.empty()) {
        std::cout << "No figures to calculate area.\n";
        return;
    }
    
    double total = 0;
    for (size_t i = 0; i < figures.size(); i++) {
        total += figures[i]->area();
    }
    std::cout << "\nTotal area of all figures: " << total << std::endl;
}

void removeFigure(Array<std::shared_ptr<Figure<double>>>& figures) {
    if (figures.empty()) {
        std::cout << "No figures to remove.\n";
        return;
    }
    
    size_t index;
    std::cout << "Enter index (0-" << figures.size() - 1 << "): ";
    std::cin >> index;
    
    if (index < figures.size()) {
        std::cout << "Removing figure [" << index << "]...\n";
        figures.remove(index);
        std::cout << "Figure removed successfully.\n";
    } else {
        std::cout << "Invalid index!\n";
    }
}

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    int choice;
    
    std::cout << "Figure Management System\n";
    std::cout << "=======================\n";
    
    while (true) {
        displayMenu();
        std::cin >> choice;
        
        if (choice == 0) {
            std::cout << "Exiting program. Goodbye!\n";
            break;
        }
        
        try {
            switch (choice) {
                case 1:
                case 2:
                case 3:
                    addFigure(figures, choice);
                    break;
                case 4:
                    displayAll(figures);
                    break;
                case 5:
                    calculateTotalArea(figures);
                    break;
                case 6:
                    removeFigure(figures);
                    break;
                case 7:
                    std::cout << "\nTotal figures: " << figures.size() << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice! Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown error occurred!\n";
        }
    }
    
    return 0;
}