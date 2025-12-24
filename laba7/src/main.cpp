#include <iostream>
#include <memory>
#include "../include/game_sys.hpp"

int main() {
    try {
        std::cout << "Da starting Faight!!!!\n";
        
        GameSystem game;
        game.initialize();
        
        game.start();
        
        std::cout << "\nPress Enter to stop the game early...\n";
        std::cin.ignore();
        
        game.stop();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}