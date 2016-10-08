#include "ring.h"

void ring_handle_change(ring *r, int *indexer, int count_change) {
    *indexer++;
    *indexer = *indexer == r->arr->capacity ? 0 : *indexer;
    r->count += count_change;
}

ring *ring_create(int capacity, int element_size) {
    ring *r = malloc(sizeof(ring));
    r->arr = array_create(capacity, element_size);
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
    int result = 0;
    if (item && r->count < r->arr->capacity) {
        result = array_set(r->arr, r->head, item);
//        r->head++;
//        r->head = r->head == r->arr->capacity ? 0 : r->head;
//        r->count++;
        ring_handle_change(r, &r->head, 1);
    }
    return result;
}

int ring_pop(ring *r, void *item) {
    int result = 0;
    if (item && r->count > 0) {
        result = array_copy_item(r->a, r->tail, item);
//        r->tail++;
//        r->tail = r->tail == r->arr->capacity ? 0 : r->tail;
//        r->count--;
        ring_handle_change(r, &r->tail, -1);
    }
    return result;
}
