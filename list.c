#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define BYTE_WIDTH 8U

list* add_item(int32_t number, list* back_item, list* next_item)
{
    list* new_item = (list*) malloc(sizeof(list));
    new_item->a = number;
    new_item->next = next_item;
    new_item->back = back_item;

    return new_item;
}

list* find_list_end(list* list_begin)
{
    list* list_end = list_begin;
    while(list_end->next != NULL)
    {
        list_end = list_end->next;
    }
    return list_end;
}

void free_list(list* item)
{
    list* back = item->back;
    list* next = item->next;
    if (back != NULL)
        back->next = next;
    if (next != NULL)
        next->back = back;
    free(item);
}

void print_item(list* item)
{
    printf("list number - %d  ", item->a);
}

void print_list(list* list_begin)
{
    list* item = list_begin;
    while(item != NULL)
    {
        printf("list number - %d\n", item->a);
        item = item->next;
    }
}

uint32_t binary_zeros(int32_t a)
{
    uint32_t mask = 1U;
    uint32_t count = 0;
    for (uint32_t i = 0; i < 4 * BYTE_WIDTH; i++)
    {
        count += (a & mask) >> i;
        mask <<= 1;
    }
    count = 4 * BYTE_WIDTH - count;

    return count;
}