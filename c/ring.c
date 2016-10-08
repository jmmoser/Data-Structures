#include "ring.h"

int ring_operation(ring *r, void *item, int(*arr_op)(array*,int,void*), int *indexer, int count_change) {
    int result = 1;
    if (item) result = arr_op(r->arr, *indexer, item);
    (*indexer)++;
    *indexer = *indexer == r->arr->capacity ? 0 : *indexer;
    r->count += count_change;
    return result;
}

ring *ring_create(int capacity, int element_size, void(*deallocator)(void *)) {
    ring *r = malloc(sizeof(ring));
    r->arr = array_create(capacity, element_size, deallocator);
    r->head = 0;
    r->tail = 0;
    r->count = 0;
    return r;
}

void ring_free(ring *r) {
    array_free(r->arr);
    free(r);
}

int ring_push(ring *r, void *item) {
    if (r->count < r->arr->capacity) {
        return ring_operation(r, item, array_set, &r->head, 1);
    }
    return 0;
}

int ring_pop(ring *r, void *item) {
    if (r->count > 0) {
        return ring_operation(r, item, array_copy_item, &r->tail, -1);
    }
    return 0;
}


