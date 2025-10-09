#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "main.h"

int valid_x(char *strx, int *x)
{
    char *endptr = NULL;

    long long pre_x = strtoll(strx, &endptr, 10);

    if(*endptr != '\0')
    {
        return INVALID_INPUT;
    }

    if (pre_x > INT_MAX || pre_x < 1)
    {
        return ERROR_OVERFLOW;
    }

    *x = (int)pre_x;

    return OK;
}

int simple_number(int x, int *res)
{
    if (x == 1) 
    {
        *res = 2;
        return OK;
    }

    int count = 1;
    int last_simple = 1;
    
    while (count < x) 
    {
        last_simple += 2;
        int is_prime = 1;
        
        for (int j = 3; j * j <= last_simple; j += 2) 
        {
            if (last_simple % j == 0) 
            {
                is_prime = 0;
                break;
            }
        }
        
        if (is_prime) 
        {
            count++;
        }
        
        if (last_simple > INT_MAX - 3) 
        {
            return ERROR_OVERFLOW;
        }
    }
    
    *res = last_simple;
    return OK;
}


int main()
{   
    int n;
    int buffer;
    printf("Input count of numbers: ");
    scanf("%d", &n);
    while ((buffer = getchar()) != '\n' && buffer != EOF);
    if (n > 1000 || n < 1)
    {
        printf("Sorry, but count must be int type and > 0 and < 1001");
        return 1;
    }

    int listn[n];
    int listres[n];
    char strx[12];
    int x;
    int sn = 1;

    printf("Input %d numbers:\n", n);
    for (int i = 0; i < n; i++)
    {
        fgets(strx, 12, stdin);

        if (strx[0] == '\n')
        {
            printf("Input empty, return please\n");
            i--;
            continue;
        }

        if(strlen(strx) == 11 && strx[10] != '\n')
        {
            printf("Error: Input too long! Maximum 11 characters, retutn please\n");
            while((buffer = getchar()) != '\n' && buffer != EOF);
            i--;
            continue;
        }

        strx[strcspn(strx, "\n")] = '\0';

        if (valid_x(strx, &x) == OK)
        {
            listn[i] = x;
        }
        else if (valid_x(strx, &x) == INVALID_INPUT)
        {
            printf("Error: It's not number, return please\n");
            i--;
        }
        else
        {
            printf("Error: Number too much or negative, return please\n");
            i--;
        }
    }

    for (int i = 0; i < n; i++)
    {
        enum errors list_error = simple_number(listn[i], &sn);
            if(list_error == ERROR_OVERFLOW)
            {
                listres[i] = 0;
            }
            else
            {
                listres[i] = sn;
            }
    }

    printf("Simple numbers:\n");
    for (int i = 0; i < n; i++)
    {
        if (listres[i] == 0)
        {
            printf("%d: Error - Number too much\n", listn[i]);
        }
        else
        {
            printf("%d: %d\n", listn[i], listres[i]);
        }   
    }

    return 0;
}
