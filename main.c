#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include "list.h"

#define FAILED_TO_CREATE_THREAD 1
#define NOT_END_THREAD 2
 

#define SIZE_OF_LIST 10
#define LOWER_BOUND -100
#define UPPER_BOUND 100

list *list_begin = NULL;
list *list_end = NULL;
list *list_back = NULL;
list *list_next = NULL;
pthread_mutex_t mutex;

/* Поиск количества нулей в списке */
void *thread_func(void *direction)
{
    uint8_t dir = *(uint8_t *) direction;
    if (dir == 1)
    {
        list_next = list_begin;
    }
    else
    {
        list_back = list_end;
    }
    while(1)
    {  
        if  (list_back == list_begin || list_next == list_end)
        {
            break;
        }

        
        if (dir == 1)
        {
            /* Подсчёт количества нулей */
            uint32_t count = binary_zeros(list_next->a);
            printf("The number of binery zeros in %d - %d\n", list_next->a, count);

            pthread_mutex_lock(&mutex);

            /* Условие завершения прохождения списка */
            if (list_next->next == list_back || list_next->next == NULL)
            {
                free_list(list_next);
                pthread_mutex_unlock(&mutex);
                break;
            }

            /* Очистка и переход к следующей позиции */
            list *next = list_next->next;
            free_list(list_next);
            list_next = next;
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            /* Подсчёт количества нулей */
            uint32_t count = binary_zeros(list_back->a);
            printf("The number of binery zeros in %d - %d\n", list_back->a, count);
            
            pthread_mutex_lock(&mutex);

            /* Условие завершения прохождения списка */
            if (list_back->back == list_next || list_back->back == NULL)
            {
                free_list(list_back);
                pthread_mutex_unlock(&mutex);
                break;
            }

            /* Очистка и переход к следующей позиции */
            list *back = list_back->back;
            free_list(list_back);
            list_back = back;
            pthread_mutex_unlock(&mutex);
        }
    }
}

/* Заполнение списка */
list *add_list()
{
    list *list_begin = NULL;
    int32_t number = LOWER_BOUND + rand() % (UPPER_BOUND + 1 - LOWER_BOUND);
    list_begin = add_item(number, NULL, NULL);
    list *plist = list_begin;
    list *new_item = NULL;
    for (int i = 1; i < SIZE_OF_LIST; i++)
    {
        number = LOWER_BOUND + rand() % (UPPER_BOUND + 1 - LOWER_BOUND);
        new_item = add_item(number, plist, NULL);
        plist->next = new_item;
        plist = plist->next;
    }
    return list_begin;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    /* Создание списка и поиск конца */
    list_begin = add_list();
    list_end = find_list_end(list_begin);
    
    print_list(list_begin);

    pthread_t pass_begin, pass_end;

    /* Прохождение списка с начала */
    uint8_t direction1 = 1;
    /* Прохождение списка с конца */
    uint8_t direction2 = 0;

    pthread_mutex_init(&mutex, NULL);

    if (pthread_create(&pass_begin, NULL, &thread_func, &direction1) != 0)
    {
        printf("Error!!! Failed to create the thread!!!\n");
        return FAILED_TO_CREATE_THREAD;
    }
    if (pthread_create(&pass_end, NULL, &thread_func, &direction2) != 0)
    {
        printf("Error!!! Failed to create the thread!!!\n");
        return FAILED_TO_CREATE_THREAD;
    }

    if (pthread_join(pass_begin, NULL) != 0)
    {
        printf("Error!!! The thread is not end!!!\n");
        return NOT_END_THREAD;
    }
    if (pthread_join(pass_end, NULL) != 0)
    {
        printf("Error!!! The thread is not end!!!\n");
        return NOT_END_THREAD;
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}