#include <stdio.h>
#include <string.h>
#include <float.h>
#include "main.h"

int valid_flag(const char *flag)
{
    if (strlen(flag) != 2)
    {
        return INVALID_INPUT;
    }

    if (flag[0] == '-' || flag[0] == '/')
    {
        switch (flag[1])
        {
            case 'q':
            case 'm':
            case 't':
                return OK;
            default:
                return INVALID_INPUT;
        }
    }
    return INVALID_INPUT;
}

int valid_for_q_and_t(const char *strx, const char *stry, const char *strz, const char *stre, float *resx, float *resy, float *resz, float *rese)
{
    char *endptr = NULL;
    double a = strtod(strx, &endptr);
    if (*endptr != '\0')
    {
        return INVALID_INPUT;
    }
    if (a > FLT_MAX || a < -FLT_MIN)
    {
        return ERROR_OVERFLOW;
    }
    *resx = (float)a;

    endptr = NULL;
    a = strtod(stry, &endptr);
    if (*endptr != '\0')
    {
        return INVALID_INPUT;
    }
    if (a > FLT_MAX || a < -FLT_MIN)
    {
        return ERROR_OVERFLOW;
    }
    *resy = (float)a;

    endptr = NULL;
    a = strtod(strz, &endptr);
    if (*endptr != '\0')
    {
        return INVALID_INPUT;
    }
    if (a > FLT_MAX || a < -FLT_MIN)
    {
        return ERROR_OVERFLOW;
    }
    *resz = (float)a;

    endptr = NULL;
    a = strtod(stre, &endptr);
    if (*endptr != '\0')
    {
        return INVALID_INPUT;
    }
    if (a > FLT_MAX || a < 0)
    {
        return ERROR_OVERFLOW;
    }
    *rese = (float)a;
    return OK;
}

int valid_for_m(const char *x, const char *y, int *resx, int *resy)
{
    char *endptr = NULL;
    long long a = strtoll(x, &endptr, 10);
    if(*endptr != '\0')
    {
        return INVALID_INPUT;
    }
    if (a > INT_MAX || a < INT_MIN)
    {
        return ERROR_OVERFLOW;
    }
    *resx = (int)a;

    endptr = NULL;
    a = strtoll(y, &endptr, 10);
    if(*endptr != '\0')
    {
        return INVALID_INPUT;
    }
    if (a > INT_MAX || a < INT_MIN)
    {
        return ERROR_OVERFLOW;
    }
    *resy = (int)a;

    return OK;
}

int flag_q(float a, float b, float c, float e, float *x1, float *x2)
{
    if (fabs(a) > e)
    {
        float D = b * b - 4 * a * c;
        if (D > e)
        {
            *x1 = (-b + sqrtf(D)) / 2 * a;
            *x2 = (-b - sqrtf(D)) / 2 * a;
            return FULL_EQUATION;
        }
        else if (fabs(D) < e)
        {
            *x1 = (-b) / 2 * a;
            return ONE_EQUATION;
        }
        else
        {
            return NO_DECISION;
        }
    }
    else if ((fabs(a) < e) && (fabs(b) > e))
    {
        *x1 = (-c) / b;
        return ONE_EQUATION;
    }
    else if ((fabs(a) < e) && (fabs(b) < e) && (fabs(c) > e))
    {
        return NO_DECISION;
    }
    else
    {
        return INFINITIVE;
    }
}

int flaq_q_out(float a, float b, float c, float e)
{   
    float x1, x2;
    enum errors errors_detected = flag_q(a, b, c, e, &x1, &x2);
    switch (errors_detected)
    {
    case FULL_EQUATION:
        printf("\nA = %.2f | B = %.2f | C = %.2f\n", a, b, c);
        printf("x1 = %.2f\nx2 = %.2f\n", x1, x2);
        break;
    case ONE_EQUATION:
        printf("\nA = %.2f | B = %.2f | C = %.2f\n", a, b, c);
        printf("x = %.2f\n", x1);
        break;
    case NO_DECISION:
        printf("\nA = %.2f | B = %.2f | C = %.2f\n", a, b, c);
        printf("No decision\n");
        break;
    case INFINITIVE:
        printf("\nA = %.2f | B = %.2f | C = %.2f\n", a, b, c);
        printf("An infinite number of solutions\n");
        break;
    default:
        break;
    }
    return OK;
}

int flag_m(int a, int b, short *res)
{
    if (a == 0 || b == 0)
    {
        return INVALID_INPUT;
    }

    if (a % b == 0)
    {
        *res = 1;
    }
    else
    {
        *res = 0;
    }

    return OK;
}

int flag_t(float a, float b, float c, float e, short *res)
{
    if (a < e || b < e || c < e)
    {
        *res = 0;
    }
    else
    {
        if ((a * a) + (b * b) - (c * c) < e)
        {
            *res = 1;
        }
        else if ((a * a) + (c * c) - (b * b) < e)
        {
            *res = 1;
        }
        else if ((b * b) + (c * c) - (a * a) < e)
        {
            *res = 1;
        }
        else
        {
            *res = 0;
        }
    }
    return OK;
}

int main(int argc, char **argv)
{
    if (argc == 4)
    {
        const char *argf = argv[1];
        const char *argx = argv[2];
        const char *argy = argv[3];
        int a, b;
        short res;
        if (valid_flag(argf) == OK && valid_for_m(argx, argy, &a, &b) == OK)
        {
            enum errors error_detecred = flag_m(a, b, &res);
            if (error_detecred == INVALID_INPUT)
            {
                printf("Numbers must be not equal 0\n");
            }
            else
            {
                if (res == 1)
                {
                    printf("A is a multiple of B\n");
                }
                else
                {
                    printf("A is a not multiple of B\n");
                }
            }
        }
        else
        {
            printf("Error: Invalid input\n");
        }

    }
    else if (argc == 6)
    {
        const char *argf = argv[1];
        const char *arge = argv[2];
        const char *argx = argv[3];
        const char *argy = argv[4];
        const char *argz = argv[5];
        float a, b, c, e;
        if (valid_flag(argf) == OK && valid_for_q_and_t(argx, argy, argz, arge, &a, &b, &c, &e) == OK)
        {   
            printf("%.5f\n", e);
            char flag = argf[1];
            switch (flag)
            {
            case 'q':
                flaq_q_out(a, b, c, e);
                flaq_q_out(a, c, b, e);
                flaq_q_out(b, a, c, e);
                flaq_q_out(b, c, a, e);
                flaq_q_out(c, a, b, e);
                flaq_q_out(c, b, a, e);
                break;
            case 't':
                {
                    short res;
                    flag_t(a, b, c, e, &res);
                    if (res == 1)
                    {
                        printf("%.2f, %.2f, %.2f are the sides of a right triangle\n", a, b, c);
                    }
                    else
                    {
                        printf("%.2f, %.2f, %.2f are NOT the sides of a right triangle\n", a, b, c);
                    }
                    break;
                }
            }
        }
        else
        {
            printf("Error: Invalid input\n");
        }
    }
    else
    {
        printf("Error: Invalid input\n");
    }
    return 0;
}