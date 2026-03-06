#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"

int valid_flag(const char *flag)
{
   if (strlen(flag) != 2 && strlen(flag) != 3)
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
                return VALID_WITH_N;
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
                return VALID_WITHOUT_N;
            default:
                return INVALID_INPUT;
        }
    }
    return INVALID_INPUT;
}

int read_file(const char *file_track, char **output)
{
    FILE *file = fopen(file_track, "r");
    if(file == NULL)
    {
        return ERROR_OPEN_FILE;
    }

    if (fseek(file, 0, SEEK_END) != 0)
    {
        fclose(file);
        return ERROR_SIZE;
    }

    long size = ftell(file);
    if (size < 0)
    {
        fclose(file);
        return ERROR_SIZE;
    }

    if (size == 0)
    {
        fclose(file);
        return ERROR_SIZE;
    }

    rewind(file);

    char *input = malloc(size + 1);
    size_t read = fread(input, 1, size, file);
    input[read] = '\0';

    fclose(file);
    
    if (read != (size_t)size)
    {
        free(input);
        return ERROR_READ_OR_WRITE;
    }

    *output = input;
    return OK;
}

int write_file(const char *file_track, char *output, short *mode)
{
    char output_filename[256];

    if (mode == 0)
    {
        snprintf(output_filename, sizeof(output_filename), "out_%s", file_track);
    }
    else
    {
        char output_filename[256];
        strcpy(output_filename, file_track);
    }

    FILE *file = fopen(output_filename, "w");
    if (file == NULL)
    {
        return ERROR_OPEN_FILE;
    }

    size_t write = fwrite(output, 1, strlen(output), file);

    if(write != strlen(output))
    {
        return ERROR_READ_OR_WRITE;
    }

    return OK;
}

int create_output_buffer(char *input, char **output)
{
    size_t size = strlen(input);
    *output = malloc(size);

    if (output == NULL)
    {
        return ERROR_SIZE;
    }

    return OK;
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
        short mode = 0;
        char *input = NULL;
        if (valid_flag(arg1) == VALID_WITHOUT_N)
        {
            enum errors errors_detected = read_file(arg2, &input);
            if (errors_detected == ERROR_OPEN_FILE)
            {
                printf("Error open file\n");
                return ERROR_OPEN_FILE;
            }
            else if(errors_detected == ERROR_SIZE)
            {
                printf("Error: file is empty or damaged\n");
                return ERROR_SIZE;
            }
            else if(errors_detected == ERROR_READ_OR_WRITE)
            {
                printf("Error of reading file\n");
                return ERROR_READ_OR_WRITE;
            }

            char *output = NULL;
            enum errors out_detected = create_output_buffer(input, &output);
            if (out_detected == ERROR_SIZE)
            {
                printf("Error: memory allocation\n");
                return ERROR_SIZE;
            }

            switch (arg1[1])
            {
            case 'd':
                flag_d(input, output);
                break;
            case 'i':
                flag_i(input, output);
                break;
            case 's':
                flag_s(input, output);
                break;
            case 'a':
                flag_a(input, output);
                break;
            }

            enum errors error_detected = write_file(arg2, output, &mode);
            if (error_detected == ERROR_OPEN_FILE)
            {
                printf("Error of opening output file\n");
                return ERROR_OPEN_FILE;
            }
            else if (error_detected == ERROR_READ_OR_WRITE)
            {
                printf("Error of writing in output file\n");
                return ERROR_READ_OR_WRITE;
            }
            else
            {
                printf("The operation was successful\n");
            }
        }
        else
        {
            printf("Error: Output file is none\n");
            return INVALID_INPUT;
        }
    }
    else if (argc == 4)
    {
        const char *arg1 = argv[1];
        const char *arg2 = argv[2];
        const char *arg3 = argv[3];
        char *input = NULL;
        short mode = 1;
        if (valid_flag(arg1) == VALID_WITH_N)
        {
            enum errors errors_detected = read_file(arg2, &input);
            if (errors_detected == ERROR_OPEN_FILE)
            {
                printf("Error open file\n");
                return ERROR_OPEN_FILE;
            }
            else if(errors_detected == ERROR_SIZE)
            {
                printf("Error: file is empty or damaged\n");
                return ERROR_SIZE;
            }
            else if(errors_detected == ERROR_READ_OR_WRITE)
            {
                printf("Error of reading file\n");
                return ERROR_READ_OR_WRITE;
            }

            char *output = NULL;
            enum errors out_detected = create_output_buffer(input, &output);
            if (out_detected == ERROR_SIZE)
            {
                printf("Error: memory allocation\n");
                return ERROR_SIZE;
            }

            switch (arg1[2])
            {
            case 'd':
                flag_d(input, output);
                break;
            case 'i':
                flag_i(input, output);
                break;
            case 's':
                flag_s(input, output);
                break;
            case 'a':
                flag_a(input, output);
                break;
            }

            enum errors error_detected = write_file(arg3, output, &mode);
            if (error_detected == ERROR_OPEN_FILE)
            {
                printf("Error of opening output file\n");
                return ERROR_OPEN_FILE;
            }
            else if (error_detected == ERROR_READ_OR_WRITE)
            {
                printf("Error of writing in output file\n");
                return ERROR_READ_OR_WRITE;
            }
            else
            {
                printf("The operation was successful\n");
            }
        }
        else
        {
            printf("Error: Flag not have 'n'\n");
            return INVALID_INPUT;
        }
    }
    else
    {
        printf("Error: Count of arg not valid\n");
        return INVALID_INPUT;
    }
    return 0;
}