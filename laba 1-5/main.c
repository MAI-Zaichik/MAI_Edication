#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"

int valid_flag(const char *flag, short *res)
{
   if (strlen(flag) != 2 || strlen(flag) != 3)
   {
        return INVALID_INPUT;
   }

    if ((flag[0] == '-' || flag[0] == '/') && flag[1] == 'n')
    {
        switch (flag[2])
        {
            case 'd':
            case 'i':
            case 's':
            case 'a':
                *res = 1;
                return OK;
            default:
                return INVALID_INPUT;
        }
    }
    else if (flag[0] == '-' || flag[0] == '/')
    {
        switch (flag[1])
        {
            case 'd':
            case 'i':
            case 's':
            case 'a':
                *res = 0;
                return OK;
            default:
                return INVALID_INPUT;
        }
    }
    return INVALID_INPUT;
}

int flag_d(char *input, char *output)
{
    int i = 0, j = 0;
    while (input[i] != '\0')
    {
        if (!isdigit(input[i]))
        {
            output[j] = input[i];
            j++;
        }
        i++;
    }
    output[j] = '\0';
    return OK;
}

int flag_i(char *input, char *output)
{
    int i = 0, j = 0;
    while (input[i] != '\0')
    {
        int k = 0, count = 0;
        char buffer[11];
        while (input[i] != '\n' || input[i] != '\0')
        {
            if (isalpha(input[i]))
            {
                count++;
            }
            i++;
        }
        itoa(k, buffer, 10);
        while (buffer[k] != '\0')
        {
            output[j] = buffer[k];
            k++;
            j++;
        }
        if (input[i] == '\n')
        {
            output[j] = '\n';
        }
        j++;
    }
    output[j] = '\0';
    return OK;
}

int flag_s(char *input, char *output)
{
    int i = 0, j = 0;
    while (input[i] != '\0')
    {
        int k = 0, count = 0;
        char buffer[11];
        while (input[i] != '\n')
        {
            if (!isalpha(input[i]) && !isdigit(input[i]) && input[i] != ' ')
            {
                count++;
            }
            i++;
        }
        itoa(k, buffer, 10);
        while (buffer[k] != '\0')
        {
            output[j] = buffer[k];
            k++;
            j++;
        }
        output[j] = '\n';
        j++;
    }
    output[j] = '\0';
    return OK;
}

int flag_a(char *input, char *output)
{
    int i = 0, j = 0;
    while (input[i] != '\0') 
    {       
        if (isdigit(input[i])) 
        {
            output[j] = input[i];
            j++;
        } 
        else 
        {
            sprintf(&output[j], "%02X", (unsigned char)input[i]);
            j += 2;
        }
        i++;
    }
    output[j] = '\0';
    return OK;
}

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        const char *arg1 = argv[1];
        const char *arg2 = argv[2];
    }
    else if (argc == 4)
    {
        const char *arg1 = argv[1];
        const char *arg2 = argv[2];
        const char *arg3 = argv[3];
    }

}