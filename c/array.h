#ifndef array_h
#define array_h

#include "byte.h"

/* Generic array structure
 */
typedef struct array {
    int element_size;
    int capacity;
    void (*deallocator)(void *);
    void *data;
} array;

array *array_create(int capacity, int element_size, void (*deallocator)(void *));

void array_free(array *a);

int array_resize(array *a, int capacity);

int array_set(array *a, int index, void *item);

void *array_get(array *a, int index);

int array_copy_item(array *a, int index, void *item);

int array_swap(array *a, int index1, int index2);

typedef struct array_iterator {
    array *a;
    
} array_iterator;

#endif
