#ifndef list_h
#define list_h

#include "common.h"

typedef struct list_node {
    int element_size;
    deallocator dealloc;
    struct list_node *next;
    struct list_node *previous;
    void *value;
} list_node;

/* Doubly linked list structure
 */
typedef struct list {
    int count;
    struct list_node *head;
    struct list_node *tail;
} list;

list *list_create();

void list_free(list *l);

int list_add(list *l, int index, void *value, int element_size, deallocator dealloc);

int list_remove(list *l, int index);


typedef struct list_iterator {
    list *l;
    list_node *node;
    int reverse;
    int index;
    void *value;
} list_iterator;

list_iterator list_get_iterator(list *l, int reverse);

void list_iterator_next(list_iterator *iterator);

#endif
