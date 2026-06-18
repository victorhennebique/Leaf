#include <assert.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "utf8proc.h"
#include "utils/unicode_string.h"
#include <scanner/scanner.h>

bool check_name_file(const char* name_file)
{
    assert(name_file != NULL);

    size_t len = strlen(name_file);
    return name_file[len-3] == '.' && name_file[len-2] == 'l' && name_file[len-1] == 'f';
}

int main(int argc, char **argv)
{
    assert(argc == 2);

    char* name_file = argv[1];
    assert(check_name_file(name_file));

    unicode_string text = scan(name_file);

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
