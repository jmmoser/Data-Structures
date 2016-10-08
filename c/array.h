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

int array_set(array *a, int idx, void *item);

void *array_get(array *a, int index);

void array_swap(array *a, int idx1, int idx2);

#endif
