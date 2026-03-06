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


int resheto(int max, int *list, int *res_list, int n)
{
    int limit;
    if (max <= 10)
        limit = 30;
    else if (max <= 100)
        limit = 550;
    else
        limit = 7920;

    // Массив для решета 
    int sieve[limit + 1];
    
    // Инициализация: все числа изначально считаем простыми
    for (int i = 0; i <= limit; i++)
    {
        sieve[i] = 1;
    }
    
    sieve[0] = sieve[1] = 0;
    
    // Массив для хранения простых чисел
    int list_of_simple_numbers[limit + 1];
    int prime_count = 0;

    for (int i = 2; i <= limit; i++)
    {
        if (sieve[i] == 1)
        {
            // Сохраняем простое число в массив
            list_of_simple_numbers[prime_count] = i;
            prime_count++;
            
            // Вычеркиваем кратные
            for (int j = i * 2; j <= limit; j += i)
            {
                sieve[j] = 0;
            }
        }

        if (prime_count == max + 1)
        {
            break;
        }
    }
    
    // Находим нужные простые числа
    for (int i = 0; i < n; i++)
    {
        int position = list[i] - 1;
        
        
        if (position >= 0 && position < prime_count)
        {
            res_list[i] = list_of_simple_numbers[position];
        }
        else
        {
            res_list[i] = 0;
        }
    }
    
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
    int max = 0;

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

            if (x > max)
            {
                max = x;
            }
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

    resheto(max, listn, listres, n);

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
