#ifndef _STRING_ARRAY_H_
#define _STRING_ARRAY_H_

#include <stddef.h>

typedef struct string_array_s {
    char **tab;
    size_t len;
} string_array;

#endif
