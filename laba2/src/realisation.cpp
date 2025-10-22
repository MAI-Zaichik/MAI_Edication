#include <stdexcept>
#include <algorithm>
#include "../include/interface.h"

using namespace std;


Decimal::Decimal()
{
    numbers.push_back(0);
}


Decimal::Decimal(const string &str)
{
    if (str.empty())
    {
        throw invalid_argument("Error: string cannot be empty");
    }

    for (size_t i = 0; i < str.size(); i++) 
    {
        if (str[i] < '0' || str[i] > '9') 
        {
            throw invalid_argument("Error: invalid character in string");
        }
    }

    for (int i = str.length() - 1; i >= 0; --i) 
    {
        numbers.push_back(str[i] - '0');
    }

    DeleteZeros();

    if(numbers.empty())
    {
        numbers.push_back(0);
    }
}


Decimal::Decimal(const Decimal &other) : numbers(other.numbers) {}


Decimal::~Decimal() noexcept {}


Decimal Decimal::add(const Decimal &other) const
{
    Decimal result;
    result.numbers.clear();

    size_t maxsize = max(numbers.size(), other.numbers.size());
    unsigned char numtransfer = 0;

    for (size_t i = 0; i < maxsize || numtransfer != 0; i++)
    {
        unsigned char sum = numtransfer;

        if (i < numbers.size())
        {
            sum += numbers[i];
        }

        if (i < other.numbers.size())
        {
            sum += other.numbers[i];
        }

        result.numbers.push_back(sum % 10);
        numtransfer = sum / 10;
    }

    result.DeleteZeros();
    return result;
}


Decimal Decimal::subtract(const Decimal &other) const
{
    if (lt(other))
    {
        throw invalid_argument("Error: Cannot subtract larger number from smaller");
    }

    Decimal result;
    result.numbers.clear();

    int borrow = 0;

    for (size_t i = 0; i < numbers.size(); i++)
    {
        int current_digit = numbers[i];
        
        current_digit -= borrow;
        borrow = 0;

        int other_digit = (i < other.numbers.size()) ? other.numbers[i] : 0;

        if (current_digit < other_digit)
        {
            current_digit += 10;
            borrow = 1;
        }

        int result_digit = current_digit - other_digit;
        result.numbers.push_back(static_cast<unsigned char>(result_digit));
    }

    if (borrow != 0)
    {
        throw logic_error("Error of subtraction");
    }

    result.DeleteZeros();

    if (result.numbers.empty())
    {
        result.numbers.push_back(0);
    }

    return result;
}


bool Decimal::eq(const Decimal &other) const
{
    return numbers == other.numbers;
}


bool Decimal::lt(const Decimal &other) const
{
    if (numbers.size() != other.size())
    {
        return numbers.size() < other.size();
    }

    for (int i = numbers.size() - 1; i >=0; i--)
    {
        if(numbers[i] != other.numbers[i])
        {
            return numbers[i] < other.numbers[i];
        }
    }

    return false;
}


bool Decimal::gt(const Decimal &other) const
{
    return !lt(other) && !eq(other);
}


string Decimal::toString() const
{
    string result;

    for(int i = numbers.size() - 1; i >= 0; i--)
    {
        result += static_cast<char>(numbers[i] + '0');
    }

    return result;
}


size_t Decimal::size() const
{
    return numbers.size();
}


void Decimal::DeleteZeros()
{
    while (numbers.size() > 1 && numbers.back() == 0)
    {
        numbers.pop_back();
    }
}
