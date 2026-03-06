#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Создание нового вектора
Vector create_vector(size_t initial_capacity, 
                     VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE), 
                     void (*DeleteFunc)(VECTOR_TYPE)) {
    Vector v;
    v.data = NULL;
    v.size = 0;
    v.capacity = 0;
    v.CopyVoidPtr = CopyFunc;
    v.DeleteVoidPtr = DeleteFunc;
    
    if (initial_capacity > 0 && CopyFunc != NULL && DeleteFunc != NULL) 
    {
        v.data = (VECTOR_TYPE*)malloc(initial_capacity * sizeof(VECTOR_TYPE));
        if (v.data != NULL) 
        {
            v.capacity = initial_capacity;
        }
    }
    
    return v;
}

// Удаление внутреннего содержимого вектора
void erase_vector(Vector *v) 
{
    if (v == NULL) return;
    
    // Удаляем каждый элемент с помощью пользовательской функции
    if (v->DeleteVoidPtr != NULL && v->data != NULL) 
    {
        for (size_t i = 0; i < v->size; i++) 
        {
            v->DeleteVoidPtr(v->data[i]);
        }
    }
    
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

// Сравнение двух векторов
int is_equal_vector(const Vector *v1, const Vector *v2) 
{
    if (v1 == NULL || v2 == NULL) return 0;
    if (v1->size != v2->size) return 0;
    
    for (size_t i = 0; i < v1->size; i++) 
    {
        if (v1->data[i] != v2->data[i]) return 0;
    }
    
    return 1;
}

// Копирование содержимого одного вектора в другой
void copy_vector(Vector *dest, const Vector *src) 
{
    if (dest == NULL || src == NULL) return;
    if (src->data == NULL && src->size > 0) return;
    
    // Очищаем целевой вектор
    erase_vector(dest);
    
    // Копируем функции
    dest->CopyVoidPtr = src->CopyVoidPtr;
    dest->DeleteVoidPtr = src->DeleteVoidPtr;
    
    // Выделяем память
    if (src->capacity > 0) 
    {
        dest->data = (VECTOR_TYPE*)malloc(src->capacity * sizeof(VECTOR_TYPE));
        if (dest->data == NULL) return;
        
        dest->capacity = src->capacity;
        dest->size = src->size;
        
        // Копируем элементы с помощью пользовательской функции копирования
        if (src->CopyVoidPtr != NULL) 
        {
            for (size_t i = 0; i < src->size; i++) 
            {
                dest->data[i] = src->CopyVoidPtr(src->data[i]);
            }
        } 
        else 
        {
            memcpy(dest->data, src->data, src->size * sizeof(VECTOR_TYPE));
        }
    }
}

// Создание нового вектора в динамической памяти
Vector* copy_vector_new(const Vector *src) 
{
    if (src == NULL) return NULL;
    
    Vector *new_vec = (Vector*)malloc(sizeof(Vector));
    if (new_vec == NULL) return NULL;
    
    // Инициализируем нулями
    new_vec->data = NULL;
    new_vec->size = 0;
    new_vec->capacity = 0;
    new_vec->CopyVoidPtr = src->CopyVoidPtr;
    new_vec->DeleteVoidPtr = src->DeleteVoidPtr;
    
    copy_vector(new_vec, src);
    
    return new_vec;
}

// Добавление элемента в конец вектора
void push_back_vector(Vector *v, VECTOR_TYPE value) 
{
    if (v == NULL) return;
    
    // Проверяем необходимость расширения
    if (v->size >= v->capacity) 
    {
        size_t new_capacity = (v->capacity == 0) ? 1 : v->capacity * 2;
        VECTOR_TYPE *new_data = (VECTOR_TYPE*)realloc(v->data, new_capacity * sizeof(VECTOR_TYPE));
        
        if (new_data == NULL) return;
        
        v->data = new_data;
        v->capacity = new_capacity;
    }
    
    // Копируем значение с помощью пользовательской функции
    if (v->CopyVoidPtr != NULL) 
    {
        v->data[v->size] = v->CopyVoidPtr(value);
    } 
    else 
    {
        v->data[v->size] = value;
    }
    
    v->size++;
}

// Удаление элемента по индексу
void delete_at_vector(Vector *v, size_t index) 
{
    if (v == NULL) return;
    if (index >= v->size) return;
    
    // Удаляем элемент с помощью пользовательской функции
    if (v->DeleteVoidPtr != NULL) 
    {
        v->DeleteVoidPtr(v->data[index]);
    }
    
    // Сдвигаем элементы влево
    for (size_t i = index; i < v->size - 1; i++) 
    {
        v->data[i] = v->data[i + 1];
    }
    
    v->size--;
}

// Получение элемента по индексу
VECTOR_TYPE get_at_vector(const Vector *v, size_t index) 
{
    if (v == NULL || index >= v->size) 
    {
        // Возвращаем значение по умолчанию
        VECTOR_TYPE default_value = {0};
        return default_value;
    }
    
    return v->data[index];
}

// Освобождение памяти, занимаемой экземпляром вектора
void delete_vector(Vector *v) 
{
    if (v == NULL) return;
    
    erase_vector(v);
    // Не освобождаем сам v, так как он может быть создан на стеке
}