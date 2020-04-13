#include "elboronlib.h"

char *combineStrings(char *one, char *two) {
    uint64_t len1 = strlen(one), len2 = strlen(two);
    char* str = malloc(len1 +len2 + 1);
    memcpy(str, one, len1);
    memcpy(str + len1, two, len2);
    str[len1 + len2] = '\0';
    return str;
}

