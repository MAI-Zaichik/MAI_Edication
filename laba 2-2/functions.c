#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

//a
void *memchr(const void *str, int c, size_t n)
{
    const unsigned char *s = (const unsigned char *)str;
    unsigned char uc = (unsigned char)c;

    for (size_t i = 0; i < n; i++)
    {
        if (s[i] == uc)
        {
            return (void *)(s + i);
        }
    }

    return NULL;
}

//b
int memcmp(const void *str1, const void *str2, size_t n)
{
    const unsigned char *s1 = (const unsigned char *)str1;
    const unsigned char *s2 = (const unsigned char *)str2;

    for (size_t i = 0; i < n; i++)
    {
        if (s1[i] == s2[i])
        {
            continue;
        }

        return (int)s1[i] - (int)s2[i];
    }

    return 0;
}

//c
void *memcpy(void *dest, const void *src, size_t n)
{
    const unsigned char *s = (const unsigned char *)src;
    unsigned char *d = (unsigned char *)dest;

    for (size_t i = 0; i < n; i++)
    {
        d[i] = s[i];
    }

    return dest;
}

//d
void *memset(void *str, int c, size_t n)
{
    unsigned char *s = (unsigned char *)str;
    unsigned char x = (unsigned char)c;

    for (size_t i = 0; i < n; i++)
    {
        s[i] = x;
    }

    return (void *)s;
}

//e
char *strncat(char *dest, const char *src, size_t n)
{
    char *s = dest;
    
    while (*s != '\0')
    {
        s++;
    }
    
    for (size_t i = 0; i < n && src[i] != '\0'; i++)
    {
        s[i] = src[i];
    }
    
    s[n] = '\0';
    
    return dest;
}

//f
char *strchr(const char *str, int c) 
{
    unsigned char uc = (unsigned char)c;
    
    while (*str != '\0') 
    {
        if (*str == uc)
        {
            return (char *)str;
        }
        str++;
    }
    
    if (uc == '\0') 
    {
        return (char *)str;
    }
    
    return NULL;
}

//g
int strncmp(const char *str1, const char *str2, size_t n)
{
    const unsigned char *s1 = (const unsigned char *)str1;
    const unsigned char *s2 = (const unsigned char *)str2;

    for (size_t i = 0; i < n; i++)
    {
        if (s1[i] != s2[i])
        {
            return (int)s1[i] - (int)s2[i];
        }
        if (s1[i] == '\0')
        {
            return 0;
        }
    }
    
    return 0;
}

//h
char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    
    for (; i < n; i++)
    {
        dest[i] = '\0';
    }
    
    return dest;
}

//i
size_t strcspn(const char *str1, const char *str2)
{
    size_t i;
    
    for (i = 0; str1[i] != '\0'; i++)
    {
        for (size_t j = 0; str2[j] != '\0'; j++)
        {
            if (str1[i] == str2[j])
            {
                return i;
            }
        }
    }
    
    return i;
}

//k
size_t strlen(const char *str)
{
    size_t i = 0;

    while (str[i] != '\0')
    {
        i++;
    }

    return i;
}

//l
char *strpbrk(const char *str1, const char *str2)
{
    for (size_t i = 0; str1[i] != '\0'; i++)
    {
        for (size_t j = 0; str2[j] != '\0'; j++)
        {
            if (str1[i] == str2[j])
            {
                return (char *)(str1 + i);
            }
        }
    }
    
    return NULL;
}

//m
char *strrchr(const char *str, int c)
{
    const char *last = NULL;
    unsigned char uc = (unsigned char)c;
    
    while (*str != '\0') 
    {
        if (*str == uc) 
        {
            last = str;
        }
        str++;
    }
    
    if (uc == '\0') 
    {
        return (char *)str;
    }
    
    return (char *)last;
}

//n
char *strstr(const char *haystack, const char *needle) 
{

    if (*needle == '\0') 
    {
        return (char *)haystack;
    }
    
    while (*haystack != '\0') 
    {
        const char *h = haystack;
        const char *n = needle;
        
        while (*h != '\0' && *n != '\0' && *h == *n) 
        {
            h++;
            n++;
        }
        
        if (*n == '\0') 
        {
            return (char *)haystack;
        }
        
        if (*h == '\0') 
        {
            return NULL;
        }
        
        haystack++;
    }
    
    return NULL;
}


//o
// переменная для предыдущего хранeния вызова
static char *save = NULL;

char *strtok(char *str, const char *delim)
{
    static char *save = NULL;
    char *token;
    
    if (str != NULL)
    {
        save = str;
    }

    else if (save == NULL)
    {
        return NULL;
    }
    
    while (*save != '\0' && strchr(delim, *save) != NULL)
    {
        save++;
    }
    
    if (*save == '\0')
    {
        save = NULL;
        return NULL;
    }

    token = save;
    
    while (*save != '\0' && strchr(delim, *save) == NULL)
    {
        save++;
    }
    
    if (*save != '\0')
    {
        *save = '\0';
        save++;
    }
    else
    {
        save = NULL;
    }
    
    return token;
}