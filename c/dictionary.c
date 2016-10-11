#include "dictionary.h"
#include "list.h"
#include <limits.h>

#include <stdio.h>

typedef struct dictionary_entry {
    char *key;
    int element_size;
    void (*deallocator)(void *);
    void *value;
} dictionary_entry;

dictionary_entry *dictionary_entry_create(char *key, void *value, int element_size, void (*deallocator)(void *)) {
    dictionary_entry *entry = malloc(sizeof(dictionary_entry));
    entry->key = strdup(key);
    entry->value = malloc(element_size);
    entry->element_size = element_size;
    entry->deallocator = deallocator;
    memcpy(entry->value, value, element_size);
    return entry;
}

void dictionary_entry_free(dictionary_entry *entry) {
    if (entry->deallocator && entry->value) {
        entry->deallocator(entry->value);
    }
    free(entry->key);
    free(entry->value);
    free(entry);
}


/* dbj2: http://www.cse.yorku.ca/~oz/hash.html
 */
int dictionary_default_hash_function(dictionary *d, char *key) {
    unsigned long int hash = 5381;
    
    int c;
    
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash % d->array->capacity;
}

void dictionary_entry_deallocator(void *item) {
    dictionary_entry_free(*(dictionary_entry **)item);
}

void dictionary_array_deallocator(void *item) {
    list_free(*(list **)item);
}

dictionary *dictionary_create(int size) {
    dictionary *d = malloc(sizeof(dictionary));
    d->array = array_create(size, sizeof(list *), dictionary_array_deallocator);
    dictionary_change_hash_function(d, dictionary_default_hash_function);
    return d;
}

void dictionary_free(dictionary *d) {
    array_free(d->array);
    free(d);
}

int dictionary_set(dictionary *d, char *key, void *value, int element_size, void(*deallocator)(void *)) {
    if (key) {
        int hash = (int)(d->hash_function)(d, key);
        
        list *l = *(list **)array_get(d->array, hash);
        if (!l) {
            l = list_create();
            array_set(d->array, hash, &l);
        }
        
        int index = -1;
        
        for (list_iterator i = list_get_iterator(l, 0); i.index >= 0; list_iterator_next(&i)) {
            dictionary_entry *existing_entry = *(dictionary_entry **)i.value;
            if (strcmp(key, existing_entry->key) == 0) {
                index = i.index;
                break;
            }
        }
        
        if (index >= 0) {
            list_remove(l, index);
        }
        
        dictionary_entry *entry = dictionary_entry_create(key, value, element_size, deallocator);
        
        list_add(l, -1, &entry, sizeof(dictionary_entry *), dictionary_entry_deallocator);
    }
    return 0;
}

void *dictionary_get(dictionary *d, char *key) {
    int hash = (int)(d->hash_function)(d, key);
    
    list *l = *(list **)array_get(d->array, hash);
    
    if (l) {
        for (list_iterator i = list_get_iterator(l, 0); i.index >= 0; list_iterator_next(&i)) {
            dictionary_entry *entry = *(dictionary_entry **)i.value;
            if (strcmp(key, entry->key) == 0) {
                return entry->value;
            }
        }
    }
    
    return 0;
}

int dictionary_remove(dictionary *d, char *key) {
    // UPDATE
    return 1;
}

void dictionary_change_hash_function(dictionary *d, int (*hash_function)(dictionary *,char *)) {
    if (hash_function) {
        d->hash_function = hash_function;
    }
}
