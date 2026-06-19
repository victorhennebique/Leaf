#include <assert.h>
#include <stdio.h>
#include "stddef.h"

#include "utils/error.h"

void msg_incorrect_extension(const char* name_file)
{
    assert(name_file != NULL);

    printf("MAIN/INCORRECT_EXTENSION: %s has not the right extension .lf.\n", name_file);
}

void msg_scanner_opening_error(char* name_file)
{
    assert(name_file != NULL);

    printf("SCANNER/OPENING_ERROR: can not open %s file.\n", name_file);
}

void msg_scanner_invalid_character(char* name_file, unsigned int line)
{
    assert(name_file != NULL);

    printf("SCANNER/INVALID_CHARACTER: can not read a character in %s file at line %d.\n", name_file, line);
}
