#include <iostream>
#include "../include/ToTurkish.h"

int main()
{
    int n;
    std::cout << "Input number: ";
    std::cin >> n;
    std::cout << ToTurkish(n) << std::endl;
    return 0;
}