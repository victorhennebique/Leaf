#include <stddef.h>

#include "../../include/utils/unicode_string.h"

struct unicode_string_s {
    utf8proc_int32_t *data;
    size_t len;
};

