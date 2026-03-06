#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <math.h>
#include <ctype.h>

Errors ValidateFloat(const char *StrNumber, double *Fnumber) 
{
    while (isspace((unsigned char)*StrNumber)) 
    {
        StrNumber++;
    }

    if (*StrNumber == '\0') 
    {
        return NOT_DIGITS_IN_NUMBER;
    }

    // из строки в дабл
    char *endptr;
    double DubNumber = strtod(StrNumber, &endptr);

    if (*endptr != '\0') 
    {
        return NOT_DIGITS_IN_NUMBER;
    }

    if (isnan(DubNumber) || isinf(DubNumber)) 
    {
        return DOUBLE_OVERFLOW;
    }

    *Fnumber = DubNumber;
    return OK_NUMBER;
}

double funcA(double x) 
{
    if (fabs(x) < EPS) return 1.0;
    return log(1 + x) / x;
}

double funcB(double x)
{
    return exp(-x * x * 0.5);
}

double funcC(double x)
{
    if (x >= 1.0 - EPS) {
        return -log(EPS);
    }
    return -log(1.0-x);
}

double funcD(double x)
{
    if (fabs(x) < EPS) return 1.0;
    return pow(x, x);
}

double TrapezoidArea(double (*function)(double x), double a, double b)
{
    return (b - a) * (function(a) + function(b)) / 2.0;
}

Errors CalculateIntegral(double (*function)(double), double a, double b, double e, double* result)
{
    if (a >= b || e <= 0 || e >= 1 || !function || !result) 
    {
        return CALC_ERROR;
    }
    
    double prev = 0; // предыдущее значение
    double current = 0; // текущее
    double step = (b - a); // шаг
    int iterations = 0; // счётчик итераций
    
    do 
    {
        prev = current;
        step /= 2;
        current = 0;
        double x = a;

        while (b - x > step / 2) 
        {
            double x_next = x + step;

            if (x_next > b || b - x_next < step / 2) 
            {
                x_next = b;
            }
            
            double value = TrapezoidArea(function, x, x_next);
            
            if (isnan(value) || isinf(value)) 
            {
                return CALC_ERROR;
            }
            
            current += value;
            
            if (isinf(current)) 
            {
                return CALC_ERROR;
            }

            x = x_next;
        }

        iterations++;

        if (iterations > MAX_ITERATIONS) 
        {
            return CALC_ERROR;
        }
        
    } while (fabs(current - prev) > e);
    
    *result = current;
    return CALC_OK;
}