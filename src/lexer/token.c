#include <assert.h>

#include "../../include/lexer/token.h"

token simple_token(token_type type)
{
    assert(type != ID);
    assert(type != NUMBER && type != REAL32 && type != REAL64);
    assert(type != CHARACTER_L && type != STRING_L);

    return type;
}

token id_token(unsigned int index)
{
    assert((index >> 24) == 0);

    return (index << 8) + ID;
}

token number_token(unsigned int index)
{
    assert((index >> 24) == 0);

    return (index << 8) + NUMBER;
}

token real32_token(unsigned int index)
{
    assert((index >> 24) == 0);

    return (index << 8) + REAL32;
}

token real64_token(unsigned int index)
{
    assert((index >> 24) == 0);

    return (index << 8) + REAL64;
}

token character_l_token(unsigned int index)
{
    assert((index >> 24) == 0);

    return (index << 8) + CHARACTER_L;
}

token string_l_token(unsigned int index)
{
    assert((index >> 24) == 0);

    return (index << 8) + STRING_L;
}
