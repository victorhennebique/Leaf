#ifndef _LEXER_H_
#define _LEXER_H_

#include <stdint.h>

#include "token.h"

typedef struct tokenized_set_s {
    token* tokenized_text;
    uint64_t* numbers;
    float* reals32;
    double* reals64;
    char* characters;
    char** strings;
    int numbers_len;
    int reals32_len;
    int reals64_len;
    int characters_len;
    int strings_len;
} tokenized_set;

tokenized_set tokenize(char* text);

#endif
