#include "byte.h"

void byte_copy(char *dst, char *src, int count) {
    for (int i = 0; i < count; i++)
        dst[i] = src[i];
}

void byte_swap(char *s1, char *s2, int count) {
    char tmp;
    for (int i = 0; i < count; i++) {
        tmp = s1[i];
        s1[i] = s2[i];
        s2[i] = tmp;
    }
}

int byte_cmp(char *s1, char *s2, int count) {
    for (int i = 0; i < count; i++)
        if (s1[i] != s2[i]) return 0;
    return 1;
}
