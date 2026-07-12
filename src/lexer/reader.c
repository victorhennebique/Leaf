#ifndef _READER_C_
#define _READER_C_

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../utils/arena.c"
#include "../utils/string.c"

typedef enum {NONE, FILE_NOT_FOUND} read_file_type;

typedef struct {
    string msg;
    read_file_type type;
} read_file_error;

typedef struct {
    union {
        string val;
        read_file_error error;
    };
    bool is_error;
} read_file_result;

read_file_result read_file_result_val(string val) {
    read_file_result res = {.is_error = false, .val = val};
    return res;
}

read_file_result read_file_result_error(read_file_type type, string msg) {
    read_file_result res = {.is_error = true, .error = {.type = type, .msg = msg}};
    return res;
}

read_file_result read_file(arena *lexer_arena, string name_file) {
    assert(lexer_arena != NULL);

    FILE *f = fopen(name_file.data, "rb");
    if (f == NULL) {
        arena *reader_arena = arena_create(50);

        string msg_start = string_explicit(reader_arena, "File not found: ");
        string msg = string_concat(lexer_arena, msg_start, name_file);

        arena_delete(reader_arena);
        return read_file_result_error(FILE_NOT_FOUND, msg);
    }

    fseek(f, 0, SEEK_END);
    size_t size_f = ftell(f);
    rewind(f);

    string buf = {.data = arena_allocate(lexer_arena, size_f + 1), .size = size_f};
    assert(buf.data != NULL);
    buf.data[size_f] = '\0';

    fread(buf.data, 1, size_f, f);
    fclose(f);

    return read_file_result_val(buf);
}

#endif
