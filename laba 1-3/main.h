#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

enum errors
{
    INVALID_INPUT,
    ERROR_OVERFLOW,
    OK,
    NO_DECISION,
    FULL_EQUATION,
    ONE_EQUATION,
    INFINITIVE
};

int valid_flag(const char *flag);
int valid_for_q_and_t(const char *strx, const char *stry, const char *strz, const char *stre, float *resx, float *resy, float *resz, float *rese);
int valid_for_m(const char *x, const char *y, int *resx, int *resy);

int flag_q(float a, float b, float c, float e, float *x1, float *x2);
int flag_t(float a, float b, float c, float e, short *res);
int flag_m(int a, int b, short *res);