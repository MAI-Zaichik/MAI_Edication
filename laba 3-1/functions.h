#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdlib.h>
#include <string.h>

enum status_codes{
    SUCCESS,
    INVALID_NUMBER,
    INVALID_R,
    NULL_POINTER,
} status_codes;

int translate_to_base(const int number, const int r, char *result);


#endif