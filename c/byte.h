#ifndef byte_h
#define byte_h

#include <stdlib.h>

void byte_copy(char *dst, char *src, int count);

void byte_swap(char *s1, char *s2, int count);

int byte_cmp(char *s1, char *s2, int count);

#endif
