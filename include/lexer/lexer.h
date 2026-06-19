#ifndef _LEXER_H_
#define _LEXER_H_

#include <stddef.h>
#include <stdint.h>

#include "token.h"
#include "utils/unicode_string.h"
#include "utils/string_array.h"
#include "utils/error.h"

typedef struct token_array_s {
    token* tab;
    size_t len;
} token_array;

token_array tokenize(unicode_string text, string_array *identifiers, unicode_string_array *litterals, error *e);

#endif
