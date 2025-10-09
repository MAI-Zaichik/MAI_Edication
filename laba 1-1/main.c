#include <stdio.h>
#include <math.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>


//преобразование х
int convert_x(const char *strx, int *x)
{
    char *endptr = NULL;

    long long pre_x = strtoll(strx, &endptr, 10);

    if(*endptr != '\0')
    {
        return INVALID_INPUT;
    }

    if (pre_x > INT_MAX || pre_x < INT_MIN)
    {
        return ERROR_OVERFLOW;
    }

    *x = (int)pre_x;

    return OK;
}

//проверка флага
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
            case 'h':
            case 'p':
            case 's':
            case 'e':
            case 'a':
            case 'f':
                return OK;
            default:
                return INVALID_INPUT;
        }
    }
    return INVALID_INPUT;
}

//флаг h
int flag_h(int x, int *res, short int *count)
{
    if (x == 0)
    {
        return INVALID_INPUT;
    }

    if (x > 100)
    {
        return ERROR_OVERFLOW;
    }

    for (int i = 0; i <= 100; i+=x)
    {
            *res = i;
            res++;
            (*count)++;
    }
    return OK;
}

//флаг p
int flag_p(int x, short int *res)
{
    if (x <= 0)
    {
        return INVALID_INPUT;
    }

    if (x == 1)
    {
        *res = 1;
        return OK;
    }

    for (int i = 2; i < x / 2; i++)
    {
        if (x % i == 0)
        {
            *res = 0;
            return OK;
        }
    }
    *res = 1;
    return OK;
}

//флаг s
int flag_s(int x, char *res, short int *lenght)
{
    unsigned int ux = (unsigned int)x;
    *lenght = snprintf(res, 9, "%x", ux);
    return OK;
}

//флаг e
int flag_e(int x, double *res)
{
    if (x > 10)
    {
        return INVALID_INPUT;
    }

    for (double i = 1; i <= x; i++)
    {
        for (double k = 1; k <= 10; k++)
        {
            *res = pow(k, i);
            res ++;
        }
    }
    return OK;
}

//флаг а
int flag_a(int x, unsigned int *res)
{
    if (x < 1)
    {
        return INVALID_INPUT;
    }

    if(x > 92681)
    {
        return ERROR_OVERFLOW;
    }
    
    if (x % 2 == 0) 
    {
        *res = (x / 2) * (unsigned int)(x + 1);
    } else 
    {
        *res = ((x + 1) / 2) * (unsigned int)x;
    }
    
    return OK;
}
//флаг f
int flag_f(int x, int *res)
{
    if (x < 1)
    {
        return INVALID_INPUT;
    }

    if (x > 12)
        {
            return ERROR_OVERFLOW;
        }

    for (int i = 1; i <= x; i++)
    {
        *res *= i;
    }
    return OK;
}

// так, ну основа, которая непосредственно всё выполняет
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Bratik, INPUT 2 ARG");
        return INVALID_INPUT;
    }

    const char *arg1 = argv[1];
    const char *arg2 = argv[2];
    
    int x = 0;

    if (convert_x(arg1, &x) == OK && valid_flag(arg2) == OK)
    {
        char flag = arg2[1];
        switch (flag)
        {
            case 'h':
            {
                int res_for_h[100];
                short int count = 0;
                enum errors error_detected = flag_h(x, res_for_h, &count);
                if (error_detected == INVALID_INPUT)
                {
                    printf("Error: Division by zero, really?");
                    return INVALID_INPUT;
                }

                if (error_detected == ERROR_OVERFLOW)
                {
                    printf("There are no such numbers");
                    return ERROR_OVERFLOW;
                }
            
                printf("Result: ");
                for (int i = 1; i < count; i++)
                {
                    printf("%d ", res_for_h[i]);
                }
                printf("\n");
                break;
            }
            case 'p':
            {
                short int res_for_p;
                enum errors error_detected = flag_p(x, &res_for_p);
                if (error_detected == INVALID_INPUT)
                {
                    printf("Error: x must be > 0");
                    return INVALID_INPUT;
                }

                if (res_for_p == 1)
                {
                    printf("X - simple number");
                }
                else
                {
                    printf("X - composite number");
                }
                break;
            }
            case 's':
            {
                char res_for_s[9];
                short int lenght = 0;
                enum errors error_detected = flag_s(x, res_for_s, &lenght);
                if (error_detected == OK)
                {
                    printf("X in Hex: ");
                    for (int i = 0; i < lenght; i++)
                    {
                        printf("%c ", res_for_s[i]);
                    }
                    printf("\n");
                }
                else
                {
                    printf("INPUT_ERROR");
                    return INVALID_INPUT;
                }
                break;
            }
            case 'e':
            {
                double res_for_e[110];
                short int lenght = 0;
                enum errors error_detected = flag_e(x, res_for_e);
                if (error_detected == INVALID_INPUT)
                {
                    printf("Error: x must be <= 10");
                    return INVALID_INPUT;
                }

                printf("|Exp/Basis |");
                for (int i = 1; i <= 10; i++)
                {
                    printf("%-11d|", i);
                }

                for (int i = 1; i <= x; i++)
                {
                    printf("\n");
                    for (int j = 0; j < 11; j++)
                    {
                        printf("------------");
                    }
                    printf("\n");
                    
                    printf("|%-10d|", i);

                    for (int k = 1; k <= 10; k++)
                    {
                        printf("%-11.0f|", res_for_e[lenght]);
                        lenght++;
                    }
                }

                printf("\n");
                    for (int j = 0; j < 11; j++)
                    {
                        printf("------------");
                    }
                printf("\n");
                break;
            }
            case 'a':
            {
                unsigned int res_for_a = 0;
                enum errors error_detected = flag_a(x, &res_for_a);
                if (error_detected == INVALID_INPUT)
                {
                    printf("Error: x must be > 0");
                    return INVALID_INPUT;
                }

                if (error_detected == ERROR_OVERFLOW)
                {
                    printf("Error: x is too big");
                    return ERROR_OVERFLOW;
                }

                printf("The amount: %u", res_for_a);
                break;
            }
            case 'f':
            {
                int res_for_f = 1;
                enum errors error_detected = flag_f(x, &res_for_f);
                if (error_detected == INVALID_INPUT)
                {
                    printf("Error: x must be > 0");
                    return INVALID_INPUT;
                }

                if (error_detected == ERROR_OVERFLOW)
                {
                    printf("Error: x is too big");
                    return ERROR_OVERFLOW;
                }

                printf("The fac: %d", res_for_f);
                break;
            }
        }
    }
    else if(convert_x(arg1, &x) == ERROR_OVERFLOW)
    {
        printf("Error: Overflow");
    }
    else
    {
        printf("x or flag do not meet the standards input");
    }
    return 0;
}