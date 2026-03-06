#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "functions.h"



int main(void) 
{
    int choice = 0;

    while (1) 
    {
        printf("\nChoise function:\n");
        printf("1. memchr\n");
        printf("2. memcmp\n");
        printf("3. memcpy\n");
        printf("4. memset\n");
        printf("5. strncat\n");
        printf("6. strchr\n");
        printf("7. strncmp\n");
        printf("8. strncpy\n");
        printf("9. strcspn\n");
        printf("10. strlen\n");
        printf("11. strpbrk\n");
        printf("12. strrchr\n");
        printf("13. strstr\n");
        printf("14. strtok\n");
        printf("0. Exit\n");

        if (scanf("%d", &choice) != 1) 
        {
            printf("Error Input.\n");
            return 1;
        }

        getchar(); 
        if (choice == 0) break;

        char str1[100], str2[100], dest[100];
        int c;
        size_t n;

        switch (choice) 
        {
            case 1:
                printf("Input string: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Input char: ");
                c = getchar();
                printf("Result: %s\n", (char *)memchr(str1, c, strlen(str1)));
                break;

            case 2:
                printf("Input first string: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Input second string: ");
                fgets(str2, sizeof(str2), stdin);
                str2[strcspn(str2, "\n")] = '\0';
                printf("Input count of bytes: ");
                scanf("%zu", &n);
                printf("Result: %d\n", memcmp(str1, str2, n));
                break;

            case 3:
                printf("Input string: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Input count of symbols for copy: ");
                scanf("%zu", &n);
                memcpy(dest, str1, n);
                dest[n] = '\0';
                printf("Result: %s\n", dest);
                break;

            case 4:
                printf("Input char: ");
                c = getchar();
                printf("Input length: ");
                scanf("%zu", &n);
                memset(dest, c, n);
                printf("Result: %s\n", dest);
                break;

            case 5:
                printf("Input dest string: ");
                fgets(dest, sizeof(dest), stdin);
                dest[strcspn(dest, "\n")] = '\0';
                printf("Input src string: ");
                fgets(str2, sizeof(str2), stdin);
                str2[strcspn(str2, "\n")] = '\0';
                printf("Input count of chars: ");
                scanf("%zu", &n);
                strncat(dest, str2, n);
                printf("Result: %s\n", dest);
                break;

            case 6:
                printf("Input string: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Input char for search: ");
                c = getchar();
                printf("Result: %s\n", strchr(str1, c));
                break;

            case 7:
                printf("Input first string: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Input second string: ");
                fgets(str2, sizeof(str2), stdin);
                str2[strcspn(str2, "\n")] = '\0';
                printf("Input count of chars for comparison: ");
                scanf("%zu", &n);
                printf("Result: %d\n", strncmp(str1, str2, n));
                break;
            case 8:
                printf("Input string for result: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Input count of chars for copy: ");
                scanf("%zu", &n);
                strncpy(dest, str1, n);
                dest[n] = '\0';
                printf("Result: %s\n", dest);
                break;

            case 9:
                printf("Input first string: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Input second string: ");
                fgets(str2, sizeof(str2), stdin);
                str2[strcspn(str2, "\n")] = '\0';
                printf("Result: %zu\n", strcspn(str1, str2));
                break;

            case 10:
                printf("Input string: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Result: %zu\n", strlen(str1));
                break;

            case 11:
                printf("Input first string: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Input string of chars for search: ");
                fgets(str2, sizeof(str2), stdin);
                str2[strcspn(str2, "\n")] = '\0';
                printf("Result: %s\n", strpbrk(str1, str2));
                break;

            case 12:
                printf("Input string: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Input char: ");
                c = getchar();
                printf("Result: %s\n", strrchr(str1, c));
                break;

            case 13:
                printf("Input string: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Input string for search: ");
                fgets(str2, sizeof(str2), stdin);
                str2[strcspn(str2, "\n")] = '\0';
                printf("Result: %s\n", strstr(str1, str2));
                break;

            case 14: {
                printf("Input string: ");
                fgets(str1, sizeof(str1), stdin);
                str1[strcspn(str1, "\n")] = '\0';
                printf("Input delim: ");
                fgets(str2, sizeof(str2), stdin);
                str2[strcspn(str2, "\n")] = '\0';
                char *token = strtok(str1, str2);
                while (token) {
                    printf("Token: %s\n", token);
                    token = strtok(NULL, str2);
                }
                break;
            }

            default:
                printf("Wrong choice.\n");
                break;
        }
    }

    printf("Bye!\n");
    return 0;
}