#include <stdio.h>
#include <stdlib.h>

enum errors
{
    INVALID_INPUT,
    ERROR_OVERFLOW,
    OK
};

int valid_x(char *strx, int *x);
int resheto(int max, int *list, int *res_list, int n);