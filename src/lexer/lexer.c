#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "lexer/lexer.h"
#include "lexer/token.h"
#include "utils/string_array.h"
#include "utils/unicode_string.h"
#include "utils/error.h"


token exclamation_mark(unicode_string lexeme, size_t *n, error *e)
{
    assert(n != NULL);

    if(lexeme.len > 1 && lexeme.data[1] == '=')
    {
        *n += 2;
        *e = NONE;
        return simple_token(DIFFERENTS);
    }
    else
    {
        *n += 1;
        *e = NONE;
        return simple_token(NOT);
    }
}

token inferior_symbol(unicode_string lexeme, size_t *n, error *e)
{
    assert(n != NULL);

    if(lexeme.len > 1 && lexeme.data[1] == '=')
    {
        *n += 2;
        *e = NONE;
        return simple_token(INF_EQ);
    }
    else
    {
        *n += 1;
        *e = NONE;
        return simple_token(INF);
    }
}

token superior_symbol(unicode_string lexeme, size_t *n, error *e)
{
    assert(n != NULL);

    if(lexeme.len > 1 && lexeme.data[1] == '=')
    {
        *n += 2;
        *e = NONE;
        return simple_token(SUP_EQ);
    }
    else
    {
        *n += 1;
        *e = NONE;
        return simple_token(SUP);
    }
}

token ampersand(unicode_string lexeme, size_t *n, error *e)
{
    assert(n != NULL);

    if(lexeme.len > 1 && lexeme.data[1] == '&')
    {
        *n += 2;
        *e = NONE;
        return simple_token(AND);
    }
    else
    {
        *e = LEXER_INVALID_LEXEME;
        return 0;
    }
}

token first_token(unicode_string lexeme, size_t *n, error *e)
{
    assert(lexeme.data != NULL);
    assert(lexeme.len > 0);
    assert(n != NULL);

    switch (lexeme.data[0]) {
        case ' ':
            *n += 1;
            lexeme.data++;
            lexeme.len--;
            return first_token(lexeme, n, e);
        case '+':
            *n += 1;
            return simple_token(PLUS);
        case '-':
            *n += 1;
            return simple_token(MINUS);
        case '*':
            *n += 1;
            return simple_token(TIMES);
        case '/':
            *n += 1;
            return simple_token(DIVIDE);
        case '%':
            *n += 1;
            return simple_token(MOD);
        case '=':
            *n += 1;
            return simple_token(EQUALS);
        case '!':
            return exclamation_mark(lexeme, n, e);
        case '<':
            return inferior_symbol(lexeme, n, e);
        case '>':
            return superior_symbol(lexeme, n, e);
        case '&':
            return ampersand(lexeme, n, e);
    }
}

token_array tokenize(unicode_string text, string_array *identifiers, unicode_string_array *litterals, error *e)
{
    assert(text.data != NULL);
    assert(identifiers != NULL);
    assert(litterals != NULL);

    token *tmp = malloc(text.len * sizeof(token));

    unicode_string lexeme = text;
    size_t count = 0;
    token tk = 1;
    while(tk > 0)
    {
        size_t n = 0;
        tk = first_token(lexeme, &n, e);

        tmp[count] = tk;

        lexeme.data += n;
        count++;
    }

    if(e != NONE)
    {

    }

}
