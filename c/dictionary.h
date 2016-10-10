#ifndef dictionary_h
#define dictionary_h

#include "array.h"

/* Hash table structure
 */
typedef struct dictionary {
    array *array;
    int (*hash_function)(struct dictionary *, char *);
} dictionary;

dictionary *dictionary_create(int size);

void dictionary_free(dictionary *d);

int dictionary_set(dictionary *d, char *key, void *value, int element_size, void(*deallocator)(void *));

void *dictionary_get(dictionary *d, char *key);

int dictionary_remove(dictionary *d, char *key);

void dictionary_change_hash_function(dictionary *d, int (*hash_function)(dictionary *,char *));

#endif
