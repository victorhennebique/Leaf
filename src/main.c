#include <assert.h>
#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <sys/time.h>

#include "utf8proc.h"
#include "utils/unicode_string.h"
#include "scanner/scanner.h"
#include "utils/error.h"


void check_extension(const char* name_file, error *e)
{
    assert(name_file != NULL);

    size_t len = strlen(name_file);

    if(name_file[len-3] == '.' && name_file[len-2] == 'l' && name_file[len-1] == 'f')
    {
        *e = NONE;
    }
    else
    {
        msg_incorrect_extension(name_file);

        *e = INCORRECT_EXTENSION;
    }
}

int main(int argc, char **argv)
{
    assert(argc == 2);
    error e;

    char* name_file = argv[1];
    check_extension(name_file, &e);
    if(e != NONE)
    {
        return e;
    }

    struct timeval t0, t1;
    gettimeofday(&t0, NULL);
    unicode_string text = scan(name_file, &e);
    gettimeofday(&t1, NULL);

    if(e != NONE)
    {
        return e;
    }

    long delta_t = (t1.tv_sec - t0.tv_sec) * 1000000 + (t1.tv_usec - t0.tv_usec);

    printf("time: %lu\n", delta_t);

    for(size_t i = 0; i < text.len; i++)
    {
        utf8proc_uint8_t buf[8];

        utf8proc_ssize_t n = utf8proc_encode_char(text.data[i], buf);

        if(n < 0)
        {
            printf("Invalid character\n");
            break;
        }

        buf[n] = '\0';

        printf("%s", buf);
    }
    printf("\n");

    free(text.data);

    return 0;
}
