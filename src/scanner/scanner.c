#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "scanner/scanner.h"
#include "utf8proc.h"
#include "utils/unicode_string.h"

unicode_string scan(char* name_file)
{
    assert(name_file != NULL);

    FILE *f = fopen(name_file, "rb");
    if(f == NULL)
    {
        perror(name_file);
        assert(false);
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

    utf8proc_int32_t* tmp = malloc(size * sizeof(utf8proc_int32_t));
    assert(tmp != NULL);

    utf8proc_uint8_t* start = norm_buf;
    size_t remaining = size;
    size_t i = 0;

    while(remaining > 0)
    {
        utf8proc_ssize_t n = utf8proc_iterate(norm_buf, -1, (tmp + i));

        if(n < 0)
        {
            printf("Invalid character in %s\n", name_file);
            break;
        }

        norm_buf += n;
        remaining -= n;
        i++;
    }

    free(start);

    size_t len = i;
    utf8proc_int32_t* data = malloc(len * sizeof(utf8proc_int32_t));
    for(size_t j = 0; j < len; j++)
    {
        data[j] = tmp[j];
    }

    free(tmp);

    unicode_string res = {.data = data, .len = len};
    return res;
}
