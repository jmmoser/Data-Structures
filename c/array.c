#include "array.h"

void array_zero(array *a, int start, int end) {
    char zero[a->element_size];
    for (int i = 0; i < a->element_size; i++) {
        zero[i] = 0;
    }
    for (int i = start; i <= end; i++) {
        array_set(a, i, zero);
    }
}

//array *array_create(int capacity, int element_size) {
//    array *a = malloc(sizeof(array));
//    a->capacity = capacity;
//    a->element_size = element_size;
//    a->data = malloc(capacity * element_size);
//    return a;
//}

array *array_create(int capacity, int element_size, void (*deallocator)(void *)) {
    array *a = malloc(sizeof(array));
//    a->capacity = capacity;
    a->capacity = 0;
    a->element_size = element_size;
//    a->data = malloc(capacity * element_size);
    a->deallocator = deallocator;
    array_resize(a, capacity);
    return a;
}

void array_free(array *a) {
    if (a->deallocator) {
        for (int i = 0; i < a->capacity; i++) {
            void *item = array_get(a, i);
            if (item) {
                a->deallocator(item);
            }
        }
    }
    free(a->data);
    free(a);
}

int array_resize(array *a, int capacity) {
    int initial_capacity = a->capacity;
    a->data = realloc(a->data, capacity * a->element_size);
    array_zero(a, initial_capacity, capacity);
    a->capacity = capacity;
    return a->data != 0;
}

int array_set(array *a, int index, void *item) {
    if (index < a->capacity) {
        void *dst = array_get(a, index);
        if (a->deallocator && dst) {
            a->deallocator(dst);
        }
        byte_copy(dst, item, a->element_size);
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
