#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

enum errors
{
    INVALID_INPUT,
    ERROR_OVERFLOW,
    OK,
    VALID_WITH_N,
    VALID_WITHOUT_N,
    ERROR_OPEN_FILE,
    ERROR_SIZE,
    ERROR_READ_OR_WRITE
};

int valid_flag(const char *flag);
int read_file(const char *file_track, char **output);
int write_file(const char *file_track, char *output, short *mode);
int create_output_buffer(char *input, char **output);

int flag_d(char *input, char *output);
int flag_i(char *input, char *output);
int flag_s(char *input, char *output);
int flag_a(char *input, char *output);