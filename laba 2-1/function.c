#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>
#include "function.h"

bool Finite_or_not(int base, int count, ...)
{
    if (base < 2 || base > 100000)
    {
        printf("Error: Base must be >= 2 <= 100000\n");
        return false;
    }

    va_list args;
    va_start(args, count);
    const double epsilon = 1e-12;

    printf("Check fractions with base %d:\n", base);

    for (int i = 0; i <= count; i++)
    {
        double fraction = va_arg(args, double);

        if (fraction - 1.0 > epsilon || fraction - 0.1 < epsilon)
        {
            printf("Error: the fraction %.10f has an incorrect range (> 1.0 or < 0.1)\n", fraction);
            continue;
        }

        printf("Fraction %.10f ", fraction);

        bool Isfinite = false;
        for (double zn = 1; zn <= 1000000; zn++)
        {
            double ch = round(fraction * zn);
            double difference = (double)ch / zn;
            //printf("%f, %f\n", zn, ch);

            if(fabs(fraction - difference) < epsilon)
            {
                int temp_zn = (int)zn;
                int temp_base = (int)base;
                //printf("BL %f, %f\n", zn, ch);

                for (int j = 2; j <= temp_base; j ++)
                    {
                        if (temp_base % j == 0 && temp_zn % j == 0)
                        {
                            bool a = false;
                            while (a == false)
                            {   
                                temp_zn /= j;
                                if (temp_zn % j == 0)
                                {
                                    continue;
                                }
                                a = true;
                            }
                        }

                        if (temp_zn == 1)
                        {
                            break;
                        }
                    }
                
                if (temp_zn == 1)
                {
                    Isfinite = true;
                    break;
                }
            }
        }

        if (Isfinite) 
        {
            printf("Is finite\n");
        } 
        else 
        {
            printf("Is infinite\n");
        }
    }

     va_end(args);
     return true;
}