#include <iostream>
#include "../include/interface.h"

int main()
{
    try
    {
        std::cout << "Run './tests/DecimalTests' for comprehensive testing." << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}