#include "functions.h"

int bit_increment(int x) 
{
    // вычисление сложения в столбик
    unsigned int remain = 1;

    while (remain) 
    {
        const unsigned int temp = x & remain; // определяем, где будут переносы (там, где 1 и в первом и во втором слагаемых)
        x = x ^ remain; // складываем без учета каких либо переносов
        remain = temp << 1; // если были переносы, то переносим в следующий разряд и складываем заново
    }

    return x;
}

int negative(int x) 
{
    // сделать отрицательное число (нужно прибавить 1, поэтому вызываем bit_increment)
    return bit_increment(~x);
}

int bit_decrement(int x) 
{
    return negative(bit_increment(negative(x)));
}


void bit_reverse(char *result, int size) 
{
    char reverse_result[size];
    int i = 0;

    size = bit_decrement(size);

    if (result[size] == '-') 
    {
        // обработка минуса
        reverse_result[i] = '-';
        i = bit_increment(i);
        size = bit_decrement(size);
    }

    while (result[size] == '0') 
    {
        // пропускаем незначащие нули
        size = bit_decrement(size);
    }

    while (size != -1) 
    {
        reverse_result[i] = result[size];
        size = bit_decrement(size);
        i = bit_increment(i);
    }

    reverse_result[i] = '\0';
    strcpy(result, reverse_result);
}


int translate_to_base(int number, const int r, char *result) 
{
    if (r < 1 || r > 5) 
    {
        return INVALID_R;
    }

    if (result == NULL) 
    {
        return NULL_POINTER;
    }

    if (number == 0) 
    {
        result[0] = '0';
        result[1] = '\0';
        return SUCCESS;
    }

    int is_negative = 0;

    if (number < 0) 
    {
        number = negative(number);
        is_negative = 1;
    }

    int index = 0;
    const unsigned int mask = bit_decrement(1 << r); // r битов '1' для получения последних r битов числа

    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    unsigned int character_id = 0;

    while (number != 0) 
    {
        character_id = number & mask;
        result[index] = digits[character_id];

        index = bit_increment(index);
        number >>= r;
    }

    if (is_negative) 
    {
        result[index] = '-';
        index = bit_increment(index);
    }

    bit_reverse(result, index);
    return SUCCESS;
}