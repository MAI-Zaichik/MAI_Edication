#include "functions.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(int argc, const char* argv[])
{
    double e;

    if (argc != 2) 
    {
        printf("Must be 1 arg\n");
        return INVALID_INPUT;
    }

    Errors parsingStatus = ValidateFloat(argv[1], &e);

    switch(parsingStatus)
    {
        case OK_NUMBER:
            break;
        case DOUBLE_OVERFLOW:
            printf("Impossible to convert: overflow\n");
            return OVERFLOW;
        case NOT_DIGITS_IN_NUMBER:
            printf("Non-digits in number: %s\n", argv[1]);
            return INVALID_INPUT;
        default:
            printf("Unexpected error\n");
            return INVALID_INPUT;
    }

    if (e <= 0.00001 || e >=1) 
    {
        printf("Epsilon must be in range [0.00001, 1]\n");
        return INVALID_INPUT;
    }

    double result = 0;

    Errors Astatus = CalculateIntegral(funcA, 0, 1, e, &result);
    if(Astatus == CALC_ERROR)
    {
        printf("There is an error during calculating\n");
    } 
    else 
    {
        printf("A: %.15lf\n", result);
    }

    result = 0;

    Errors Bstatus = CalculateIntegral(funcB, 0, 1, e, &result);

    if(Bstatus == CALC_ERROR)
    {
        printf("There is an error during calculating\n");
    } 
    else 
    {
        printf("B: %.15lf\n", result);
    }

    result = 0;

    Errors Cstatus = CalculateIntegral(funcC, 0, 1, e, &result);
    if(Cstatus == CALC_ERROR)
    {
        printf("There is an error during calculating\n");
    } 
    else 
    {
        printf("C: %.15lf\n", result);
    }

    result = 0;

    Errors Dstatus = CalculateIntegral(funcD, 0, 1, e, &result);
    if(Dstatus == CALC_ERROR)
    {
        printf("There is an error during calculating\n");
    } 
    else 
    {
        printf("D: %.15lf\n", result);
    }

    return 0;
}