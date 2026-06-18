#ifndef _UNICODE_STRING_H_
#define _UNICODE_STRING_H_

#include <stddef.h>

#include "utf8proc.h"

typedef struct unicode_string_s {
    utf8proc_int32_t* data;
    size_t len;
} unicode_string;

#endif
