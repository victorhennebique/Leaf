#include <stdio.h>
#include <utf8proc.h>

int main(void)
{
    utf8proc_int32_t cp;

    utf8proc_ssize_t n = utf8proc_iterate((const utf8proc_uint8_t *)"é", -1, &cp);

    if (n < 0) {
        fprintf(stderr, "UTF-8 invalide\n");
        return 1;
    }

    printf("U+%04X\n", cp);

    return 0;
}
