#include <stdio.h>
#include <stdlib.h>

enum errors
{
    INVALID_INPUT,
    ERROR_OVERFLOW,
    OK
};

int valid_x(char *strx, int *x);
int simple_number(int x, int *res);
