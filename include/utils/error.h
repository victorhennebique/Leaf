#ifndef _ERROR_H_
#define _ERROR_H_

#include "utils/unicode_string.h"
typedef enum error_e {
    NONE,
    INCORRECT_EXTENSION,
    SCANNER_OPENING_ERROR,
    SCANNER_INVALID_CHAR,
    LEXER_INVALID_LEXEME
} error;

void msg_incorrect_extension(const char* name_file);

void msg_scanner_opening_error(char* name_file);

void msg_scanner_invalid_character(char* name_file, unsigned int line);

void msg_lexer_invalid_lexeme(char* name_file, unicode_string text, unsigned int i);

#endif
