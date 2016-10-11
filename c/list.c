#include "list.h"
#include <stdlib.h>
#include <string.h>

list_node *list_node_create(void *value, int element_size, void (*deallocator)(void *)) {
    list_node *node = malloc(sizeof(list_node));
    node->element_size = element_size;
    node->deallocator = deallocator;
    node->next = 0;
    node->previous = 0;
    node->value = malloc(element_size);
    memcpy(node->value, value, element_size);
//    byte_copy(node->value, value, element_size);
    return node;
}

list_node *list_node_free(list_node *node) {
    list_node *next = node->next;
    if (node->deallocator && node->value) {
        node->deallocator(node->value);
    }
    free(node->value);
    free(node);
    return next;
}

list *list_create() {
    list *l = malloc(sizeof(list));
    l->count = 0;
    l->head = 0;
    l->tail = 0;
    return l;
}

void list_free(list *l) {
    list_node *next = l->head;
    while (next) {
        next = list_node_free(next);
    }
    free(l);
}

int list_add(list *l, int index, void *value, int element_size, void (*deallocator)(void *)) {
    
    list_node *new_node = list_node_create(value, element_size, deallocator);
    
    list_node *node = 0;
    
    l->count++;
    
    if (l->count > 1) {
        
        index %= l->count;
        
        if (index >= 0) {
            
            node = l->head;
            
            while (index--, node && index >= 0) {
                node = node->next;
            }
            
            if (node == l->head) {
                l->head = new_node;
            }
            
            new_node->next = node;
            new_node->previous = node->previous;
            if (node->previous) node->previous->next = new_node;
            node->previous = new_node;
        } else {
            
            node = l->tail;
            
            while (index++, node && index < 0) {
                node = node->previous;
            }
            
            if (node == l->tail) {
                l->tail = new_node;
            }
            
            new_node->next = node->next;
            new_node->previous = node;
            if (node->next) node->next->previous = new_node;
            node->next = new_node;
        }
    } else {
        l->head = new_node;
        l->tail = new_node;
    }
    
    return 1;
}

int list_remove(list *l, int index) {
    int actual_index;
    if (l->count > 0) {
        
        index %= l->count;
        actual_index = index >= 0 ? index : l->count + index;
        
        list_node *node = 0;
        
        for (list_iterator i = list_get_iterator(l, index < 0); i.index >= 0; list_iterator_next(&i)) {
            if (i.index == actual_index) {
                node = i.node;
                break;
            }
        }
        
        if (node) {
            if (node->previous) node->previous->next = node->next;
            if (node->next) node->next->previous = node->previous;
            if (node == l->head) l->head = node->next;
            if (node == l->tail) l->tail = node->previous;
            
            list_node_free(node);
            l->count--;
            return 1;
        }
    }
    return 0;
}

list_iterator list_get_iterator(list *l, int reverse) {
    list_iterator iterator;
    if (l->count > 0) {
        iterator.l = l;
        iterator.reverse = reverse;
        iterator.node = reverse ? l->tail : l->head;
        iterator.index = reverse ? l->count - 1 : 0;
        iterator.value = iterator.node->value;
    } else {
        iterator.index = -1;
    }
    return iterator;
}

void list_iterator_next(list_iterator *iterator) {
    if (iterator->node) {
        if (iterator->reverse) {
            iterator->index--;
            iterator->node = iterator->node->previous;
            if (iterator->node) {
                iterator->value = iterator->node->value;
            } else {
                iterator->index = -1;
            }
        } else {
            iterator->index++;
            iterator->node = iterator->node->next;
            if (iterator->node) {
                iterator->value = iterator->node->value;
            } else {
                iterator->index = -1;
            }
        }
    }
}
