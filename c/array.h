#ifndef array_h
#define array_h

#include "byte.h"

typedef struct array {
    void *data;
    int es;
    int capacity;
} array;

array *array_create(int capacity, int element_size);

void array_free(array *a);

int array_resize(array *a, int capacity);

int array_set(array *a, int index, void *item);

void *array_get(array *a, int index);

int array_copy_item(array *a, int index, void *item);

void array_swap(array *a, int index1, int index2);

#endif
