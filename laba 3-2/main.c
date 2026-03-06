#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Определяем тип элементов вектора как int
#define VECTOR_TYPE int
#include "functions.h"

// Функции копирования и удаления для int
int copy_int(int value) 
{
    return value;  // Поверхностное копирование для int
}

void delete_int(int value) 
{
    // Для int ничего делать не нужно
    (void)value;
}

void print_vector(const Vector *v, const char *name) 
{
    if (v == NULL) {
        printf("%s: NULL\n", name);
        return;
    }
    printf("%s: size=%zu, capacity=%zu, data=[", name, v->size, v->capacity);
    for (size_t i = 0; i < v->size; i++) {
        printf("%d", v->data[i]);
        if (i < v->size - 1) printf(", ");
    }
    printf("]\n");
}

int main() 
{
    printf("=== Демонстрация работы библиотеки Vector (тип int) ===\n\n");
    
    // 1. Создание вектора
    printf("1. Создание вектора с начальной емкостью 3:\n");
    Vector v1 = create_vector(3, copy_int, delete_int);
    print_vector(&v1, "v1");
    
    // 2. Добавление элементов
    printf("\n2. Добавление элементов (push_back):\n");
    for (int i = 0; i < 5; i++) {
        push_back_vector(&v1, i * 10);
        printf("   Добавлен %d\n", i * 10);
    }
    print_vector(&v1, "v1");
    
    // 3. Получение элемента по индексу
    printf("\n3. Получение элементов по индексу:\n");
    for (size_t i = 0; i < v1.size + 1; i++) {
        int val = get_at_vector(&v1, i);
        if (i < v1.size) {
            printf("   v1[%zu] = %d\n", i, val);
        } else {
            printf("   v1[%zu] = %d (некорректный индекс)\n", i, val);
        }
    }
    
    // 4. Копирование вектора
    printf("\n4. Копирование вектора:\n");
    Vector v2 = create_vector(0, copy_int, delete_int);
    copy_vector(&v2, &v1);
    print_vector(&v2, "v2 (копия v1)");
    
    // 5. Сравнение векторов
    printf("\n5. Сравнение векторов:\n");
    printf("   v1 и v2 %s\n", is_equal_vector(&v1, &v2) ? "равны" : "не равны");
    
    // Изменяем v2 и сравниваем снова
    push_back_vector(&v2, 999);
    printf("   После добавления 999 в v2:\n");
    printf("   v1 и v2 %s\n", is_equal_vector(&v1, &v2) ? "равны" : "не равны");
    
    // 6. Создание нового вектора в динамической памяти
    printf("\n6. Создание нового вектора в динамической памяти:\n");
    Vector *v3 = copy_vector_new(&v1);
    if (v3) {
        print_vector(v3, "v3 (динамический)");
    } else {
        printf("   Ошибка создания динамического вектора\n");
    }
    
    // 7. Удаление элемента по индексу
    printf("\n7. Удаление элемента по индексу:\n");
    print_vector(&v1, "v1 до удаления");
    delete_at_vector(&v1, 2);
    printf("   Удаление индекса 2\n");
    print_vector(&v1, "v1 после удаления");
    
    // Попытка удаления с неверным индексом
    printf("   Попытка удаления индекса 100 (игнорируется)\n");
    delete_at_vector(&v1, 100);
    print_vector(&v1, "v1 после попытки");
    
    // 8. Очистка внутреннего содержимого
    printf("\n8. Очистка внутреннего содержимого (erase):\n");
    print_vector(&v2, "v2 до erase");
    erase_vector(&v2);
    print_vector(&v2, "v2 после erase");
    
    // 9. Освобождение памяти
    printf("\n9. Освобождение памяти:\n");
    delete_vector(&v1);
    delete_vector(&v2);
    delete_vector(v3);
    free(v3);  // Освобождаем саму структуру для динамического вектора
    printf("   Память освобождена\n");
    
    // 10. Демонстрация работы с NULL
    printf("\n10. Демонстрация работы с NULL указателями:\n");
    printf("   push_back с NULL (игнорируется)\n");
    push_back_vector(NULL, 42);
    
    printf("   delete_at с NULL (игнорируется)\n");
    delete_at_vector(NULL, 0);
    
    printf("   get_at с NULL: %d\n", get_at_vector(NULL, 0));
    
    printf("\n=== Демонстрация завершена ===\n");
    return 0;
}