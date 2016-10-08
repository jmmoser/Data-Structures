#ifndef ring_h
#define ring_h

#include "array.h"

/* Circular buffer structure
*/
typedef struct ring {
    array *arr;
    int count;
    int lastIndex;
    int head;
    int tail;
} ring;

ring *ring_create(int capacity, int element_size);

void ring_free(ring *r);

int ring_push(ring *r, void *item);

int ring_pop(ring *r, void *item);

#endif
