#include "array.h"
#include <stdlib.h>
#include <string.h>

void byte_swap(char *s1, char *s2, int count) {
    char tmp;
    for (int i = 0; i < count; i++) {
        tmp = s1[i];
        s1[i] = s2[i];
        s2[i] = tmp;
    }
}

void array_zero(array *a, int start, int end) {
    char zero[a->element_size];
    for (int i = 0; i < a->element_size; i++) {
        zero[i] = 0;
    }
    for (int i = start; i < end; i++) {
        memcpy(array_get(a, i), zero, a->element_size);
    }
}

array *array_create(int capacity, int element_size, deallocator dealloc) {
    array *a = malloc(sizeof(array));
    a->data = 0;
    a->capacity = 0;
    a->element_size = element_size;
    a->dealloc = dealloc;
    array_resize(a, capacity);
    return a;
}

void array_item_free(array *a, void *item) {
    if (*(int *)item != 0) {
        a->dealloc(item);
    }
}

void array_free(array *a) {
    if (a->dealloc) {
        for (int i = 0; i < a->capacity; i++) {
            array_item_free(a, array_get(a, i));
        }
    }
    free(a->data);
    free(a);
}

int array_resize(array *a, int capacity) {
    int initial_capacity = a->capacity;
    a->data = realloc(a->data, capacity * a->element_size);
    a->capacity = capacity;
    array_zero(a, initial_capacity, capacity);
    return a->data != 0;
}

int array_set(array *a, int index, void *item) {
    if (index < a->capacity) {
        void *dst = array_get(a, index);
        if (a->dealloc) {
            array_item_free(a, dst);
        }
        memcpy(dst, item, a->element_size);
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
    if (item && index < a->capacity) {
        memcpy(item, array_get(a, index), a->element_size);
        return 1;
    }

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
