#include "heap.h"

int heap_parent(int idx) {
    return ((idx + 1) >> 1) - 1;
}

int heap_left(int idx) {
    return ((idx + 1) << 1) - 1;
}

int heap_right(int idx) {
    return (idx + 1) << 1;
}

heap *heap_create(int capacity, int element_size, int (*comparator)(void*,void*), void (*deallocator)(void *)) {
    heap *h = malloc(sizeof(heap));
    h->top = -1;
    h->arr = array_create(capacity, element_size, deallocator);
    h->comparator = comparator;
    return h;
}

void heap_free(heap *h) {
    array_free(h->arr);
    free(h);
}

void heap_sift_down(heap *h, int idx, int end) {
    int parentIdx;
    while (parentIdx = heap_parent(idx), idx > end) {
        if (h->comparator(array_get(h->arr, idx),array_get(h->arr, parentIdx)) > 0) {
            array_swap(h->arr, idx, parentIdx);
            idx = parentIdx;
        } else {
            break;
        }
    }
}

void heap_percolate_up(heap *h, int idx) {
    int lc, rc;
    while (lc = heap_left(idx), rc = lc + 1, lc <= h->top) {
        if (rc <= h->top && h->comparator(array_get(h->arr, rc), array_get(h->arr, lc)) > 0) {
            heap_sift_down(h, rc, idx);
            idx = rc;
        } else {
            heap_sift_down(h, lc, idx);
            idx = lc;
        }
    }
}

void heap_push(heap *h, void *value) {
    h->top++;
    array_set(h->arr, h->top, value);
    heap_sift_down(h, h->top, 0);
}

int heap_pop(heap *h, void *dst) {
    if (h->top >= 0) {
        if (dst) array_copy_item(h->arr, 0, dst);
        array_copy_item(h->arr, h->top, array_get(h->arr, 0));
        h->top--;
        heap_percolate_up(h, 0);
        return 1;
    }
    return 0;
}

void heap_replace(heap *h, int index, void *value, void *dst) {
    if (dst) array_copy_item(h->arr, index, dst);
    array_set(h->arr, index, value);
    heap_percolate_up(h, index);
}

int heap_delete(heap *h, int index) {
    if (index >= 0 && index <= h->top) {
        h->top--;
        heap_replace(h, index, array_get(h->arr, h->top + 1), 0);
        return 1;
    }
    return 0;
}

int heap_find(heap *h, int (*iterator)(void *element, void *context), void *context) {
    if (iterator) {
        for (int i = 0; i <= h->top; i++) {
            if (iterator(array_get(h->arr, i), context)) {
                return i;
            }
        }
    }
    return -1;
}

void *heap_peak(heap *h) {
    return array_get(h->arr, 0);
}
