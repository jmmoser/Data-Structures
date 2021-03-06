#ifndef array_h
#define array_h

#include "common.h"

/* Generic array structure
 */
typedef struct array {
    int element_size;
    int capacity;
    deallocator dealloc;
    void *data;
} array;

array *array_create(int capacity, int element_size, deallocator dealloc);

void array_free(array *a);

int array_resize(array *a, int capacity);

int array_set(array *a, int index, void *item);

void *array_get(array *a, int index);

int array_copy_item(array *a, int index, void *item);

int array_swap(array *a, int index1, int index2);

#endif
