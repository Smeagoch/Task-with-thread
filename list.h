#include <stdio.h>
#include <stdint.h>

#ifndef LIST_H
#define LIST_H

typedef struct list
{
    int32_t a;          /* Значение */
    struct list* back;  /* Предыдущий элемент */
    struct list* next;  /* Следующий элемент */
}list; 

/* Добавление новой позиции в список */
list* add_item(int32_t number, list* back_item, list* next_item);

/* Поиск конца списка */
list* find_list_end(list* list_begin);

/* Очистка позиции */
void free_list(list* item);

void print_list(list* list_begin);

/* Подсчёт количества бинарных нулей в числу */
uint32_t binary_zeros(int32_t a);

#endif /* LIST_H */