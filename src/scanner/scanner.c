#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "scanner/scanner.h"
#include "utf8proc.h"
#include "utils/error.h"
#include "utils/unicode_string.h"


unicode_string scan(char* name_file, error *e)
{
    assert(name_file != NULL);

    FILE *f = fopen(name_file, "rb");
    if(f == NULL)
    {
        msg_scanner_opening_error(name_file);

        *e = SCANNER_OPENING_ERROR;
        unicode_string res = {.data = NULL, .len = 0};
        return res;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buf = malloc(size + 1);
    assert(buf != NULL);

    fread(buf, 1, size, f);
    fclose(f);

    buf[size] = '\0';

    utf8proc_uint8_t* norm_buf = utf8proc_NFC((utf8proc_uint8_t*)buf);
    free(buf);

    size_t bytes = strlen((char *)norm_buf);
    utf8proc_int32_t* tmp = malloc(bytes * sizeof(utf8proc_int32_t));
    assert(tmp != NULL);

    utf8proc_uint8_t* start = norm_buf;
    size_t i = 0;
    unsigned int line = 1;

    while(norm_buf[0] != '\0')
    {
        utf8proc_ssize_t n = utf8proc_iterate(norm_buf, -1, (tmp + i));

        if(n < 0)
        {
            msg_scanner_invalid_character(name_file, line);

            unicode_string res = {.data = NULL, .len = norm_buf - start};

            free(tmp);
            free(start);

            *e = SCANNER_INVALID_CHAR;
            return res;
        }

        norm_buf += n;
        i++;
    }

    free(start);

    size_t len = i;
    utf8proc_int32_t* data = malloc((len + 1) * sizeof(utf8proc_int32_t));
    for(size_t j = 0; j < len; j++)
    {
        data[j] = tmp[j];
    }
    data[len] = '\0';

    free(tmp);

    *e = NONE;
    unicode_string res = {.data = data, .len = len};
    return res;
}
