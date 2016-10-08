#include "array.h"

array *array_create(int capacity, int element_size) {
    array *a = malloc(sizeof(array));
    a->capacity = capacity;
    a->element_size = element_size;
    a->data = malloc(capacity * element_size);
    return a;
}

void array_free(array *a) {
    free(a->data);
    free(a);
}

int array_resize(array *a, int capacity) {
    a->capacity = capacity;
    a->data = realloc(a->data, capacity * a->element_size);
    return a->data != 0;
}

int array_set(array *a, int idx, void *item) {
    if (idx < a->capacity) {
        byte_copy(a->data + idx * a->element_size, item, a->element_size);
        return 1;
    }
    return 0;
}

void *array_get(array *a, int index) {
    if (index < a->capacity)
        return a->data + index * a->element_size;
    
    return 0;
}

int array_copy_item(array *a, int index, void *item) {
    if (item && index < a->capacity)
        byte_copy(item, array_get(a, index), a->element_size);
        return 1;
    
    return 0;
}

int array_swap(array *a, int index1, int index2) {
    if (index1 != index2) {
        void *item1 = array_get(a, index1);
        void *item2 = array_get(a, index2);
        if (item1 && item2) {
            byte_swap(item1, item2, a->element_size);
            return 1;
        }
    }
    return 0;
}
