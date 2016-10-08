#ifndef heap_h
#define heap_h

#include "array.h"

/* Binary heap structure
 */
typedef struct heap {
    int top;
    array *arr;
    int (*comparator)(void*,void*);
} heap;

/* For a min-heap the comparator should return 1 if a < b and -1 if a > b.
 * For a max-heap the comparator should return 1 if a > b and -1 if a < b.
 */
heap *heap_create(int capacity, int element_size, int (*comparator)(void *a,void *b));

void heap_free(heap *h);

void heap_push(heap *h, void *value);

int heap_pop(heap *h, void *dst);

void *heap_peak(heap *h);

void heap_replace(heap *h, int index, void *value, void *dst);

int heap_delete(heap *h, int index);

int heap_find(heap *h, int (*iterator)(void *element, void *context), void *context);

#endif
