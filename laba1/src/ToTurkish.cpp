#include <string>
#include <unordered_map>
#include "../include/ToTurkish.h"

std::string ToTurkish(int x)
{
    if (x < 0 || x > 99)
    {
        return "Error: number must be > 0 and < 100";
    }

    std::unordered_map<int, std::string> units = 
    {
        {0, "sifir"},
        {1, "bir"},
        {2, "iki"},
        {3, "üç"},
        {4, "dört"},
        {5, "beş"},
        {6, "alti"},
        {7, "yedi"},
        {8, "sekiz"},
        {9, "dokuz"}
    };

    std::unordered_map<int, std::string> tens =
    {
        {10, "on"},
        {20, "yirmi"},
        {30, "otuz"},
        {40, "kirk"},
        {50, "elli"},
        {60, "altmiş"},
        {70, "yetmiş"},
        {80, "seksen"},
        {90, "doksan"}
    };

    if (x < 10)
    {
        return units[x];
    }

    if (x % 10 == 0)
    {
        return tens[x];
    }

    int x_ten = (x / 10) * 10;
    int x_unit = x % 10;

    return tens[x_ten] + " " + units[x_unit];
}
