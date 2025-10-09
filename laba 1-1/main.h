#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

enum errors
{
    INVALID_INPUT,
    ERROR_OVERFLOW,
    OK
};

int convert_x(const char *strx, int *x);
int valid_flag(const char *flag);

int flag_h(int x, int *res, short int *count);
int flag_p(int x, short int *res);
int flag_s(int x, char *res, short int *lenght);
int flag_e(int x, double *res);
int flag_a(int x, unsigned int *res);
int flag_f(int x, int *res);