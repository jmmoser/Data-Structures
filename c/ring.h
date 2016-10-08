#ifndef heap_h
#define heap_h

#include "array.h"

typedef struct ring {
    array *arr;
    int count;
    int lastIndex;
    int head;
    int tail;
} ring;

ring *ring_create(int capacity, int element_size);

void ring_free(ring *r);

#endif
