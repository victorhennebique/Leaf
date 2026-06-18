#include <assert.h>
#include <stddef.h>

#include "lexer/token.h"

token simple_token(token_type type)
{
    assert(type != ID && type != LITTERAL);

    return type;
}

token id_token(unsigned int index)
{
    assert((index >> 24) == 0);

    return (index << 8) + ID;
}

token litteral_token(unsigned int index)
{
    assert((index >> 24) == 0);

    return (index << 8) + LITTERAL;
}

