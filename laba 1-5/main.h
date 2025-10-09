#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

enum errors
{
    INVALID_INPUT,
    ERROR_OVERFLOW,
    OK
};

int valid_flag(const char *flag, short *res);
int flag_d(char *input, char *output);
int flag_i(char *input, char *output);
int flag_s(char *input, char *output);
int flag_a(char *input, char *output);