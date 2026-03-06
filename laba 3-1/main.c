#include "functions.h"
#include <stdio.h>

int main() 
{
    const int BUF_SIZE = 50;
    char result[BUF_SIZE];
    int number, r;
    char choice;

    do 
    {
        printf("Input number for convert: ");
        if (scanf("%d", &number) != 1) 
        {
            printf("Error input!\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Input r (1-5): ");

        if (scanf("%d", &r) != 1) 
        {
            printf("Error input r!\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        int status_code = translate_to_base(number, r, result);
        
        if (status_code == SUCCESS) 
        {
            printf("\nResult:\n");
            printf("Original number: %d\n", number);
            printf("Basis: 2^%d = %d\n", r, 1 << r);
            printf("Result: %s\n\n", result);
        } 
        else if (status_code == INVALID_R) 
        {
            printf("Error: r must be [1, 5]\n\n");
        } 
        else if (status_code == NULL_POINTER) 
        {
            printf("Error: Null pointer\n\n");
        } 
        else 
        {
            printf("Unknown error: %d\n\n", status_code);
        }

        printf("Continue? (y/n): ");
        scanf("%c", &choice);
        while (getchar() != '\n'); // очистка буфера

    } while (choice == 'y' || choice == 'Y');

    printf("Programm out.\n");
    return 0;
}