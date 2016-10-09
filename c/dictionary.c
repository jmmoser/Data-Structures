#include "dictionary.h"
#include "list.h"

typedef struct dictionary_entry {
    char *key;
    void *value;
    int element_size;
    void (*deallocator)(void *);
} dictionary_entry;

int dictionary_default_hash_function(char *key) {
    return 1;
}

void dictionary_entry_deallocator(void *item) {
    dictionary_entry *entry = (dictionary_entry *)item;
    free(entry->key);
    if (entry->deallocator) {
        entry->deallocator(entry->value);
    }
    free(entry);
}

dictionary *dictionary_create(int size) {
    dictionary *d = malloc(sizeof(dictionary));
    d->array = array_create(size, sizeof(dictionary_entry *), dictionary_entry_deallocator);
    return d;
}

void dictionary_free(dictionary *d) {
    array_free(d->array);
    free(d);
}

int dictionary_set(dictionary *d, char *key, void *value, int element_size, void(*deallocator)(void *)) {
    return 1;
}

int dictionary_get(dictionary *d, char *key) {
    return 1;
}

int dictionary_remove(dictionary *d, char *key) {
    return 1;
}

void dictionary_change_hash_function(dictionary *d, int (*hash_function)(char *)) {
    if (hash_function) {
        d->hash_function = hash_function;
    }
}
