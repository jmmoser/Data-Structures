#include "array.h"

array *array_create(int capacity, int element_size) {
    array *a = malloc(sizeof(array));
    a->capacity = capacity;
    a->es = element_size;
    a->data = malloc(capacity * element_size);
    return a;
}

void array_free(array *a) {
    free(a->data);
    free(a);
}

int array_resize(array *a, int capacity) {
    a->capacity = capacity;
    a->data = realloc(size * capacity);
    return a->data != 0;
}

int array_set(array *a, int idx, void *item) {
    if (idx < a->capacity) {
        byte_copy(a->data + idx * a->es, item, a->es);
        return 1;
    }
    return 0;
}

void *array_get(array *a, int index) {
    if (index < a->capacity)
        return a->data + index * a->es;
    
    return 0;
}

int array_copy_item(array *a, int index, void *item) {
    if (item && index < a->capacity)
        byte_copy(item, array_get(index), a->element_size);
        return 1;
    
    return 0;
}

void array_swap(array *a, int idx1, int idx2) {
    if (idx1 != idx2 && idx1 < a->capacity && idx2 < a->capacity) {
        byte_swap(a->data + idx1 * a->es, a->data + idx2 * a->es, a->es);
    }
}
