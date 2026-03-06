#ifndef DEF_H
#define DEF_H
#include <stddef.h>

#define MAX_ITERATIONS 1000000
#define EPS 1e-12

typedef enum {
    // Основные
    OK_INPUT,
    INVALID_INPUT,
    OVERFLOW,
    MEMORY_ERROR,
    
    // Валидация е
    NUMBER_INT_OVERFLOW,
    NOT_POSITIVE_NUMBER,
    NOT_DIGITS_IN_NUMBER,
    DOUBLE_OVERFLOW,
    OK_NUMBER,
    
    // Статусы вычислений
    CALC_ERROR,
    CALC_OK
} Errors;

Errors ValidateFloat(const char *StrNumber, double *Fnumber);
Errors CalculateIntegral(double (*function)(double), double a, double b, double e, double* result);
double TrapezoidArea(double (*function)(double x), double a, double b);
double funcA(double x);
double funcB(double x);
double funcC(double x);
double funcD(double x);

#endif