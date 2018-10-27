#ifndef heap_h
#define heap_h

#include "common.h"
#include "array.h"

/* Binary heap structure
 */
typedef struct heap {
    int top;
    array *array;
    int (*comparator)(void*,void*);
} heap;

/* For a min-heap the comparator should return 1 if item1 < item2 and -1 if item1 > item2.
 * For a max-heap the comparator should return 1 if item1 > item2 and -1 if item1 < item2.
 */
heap *heap_create(int capacity, int element_size, int (*comparator)(void *item1,void *item2), deallocator dealloc);

void heap_free(heap *h);

void heap_push(heap *h, void *value);

int heap_pop(heap *h, void *dst);

void *heap_peak(heap *h);

void heap_replace(heap *h, int index, void *value, void *dst);

int heap_delete(heap *h, int index);

int heap_find(heap *h, int (*iterator)(void *element, void *context), void *context);

#endif
