#include <stdio.h>
#include <stdint.h>

#ifndef LIST_H
#define LIST_H

typedef struct list
{
    int32_t a;
    struct list* back;
    struct list* next;
}list; 

//Adding a new position to the list
list* add_item(int32_t number, list* back_item, list* next_item);

//Finding the end of the list
list* find_list_end(list* list_begin);

void print_item(list* item);

//Cliaring the list
void free_list(list* item);

void print_list(list* list_begin);

//Search the number of binary zeros
uint32_t binary_zeros(int32_t a);

#endif /* LIST_H */