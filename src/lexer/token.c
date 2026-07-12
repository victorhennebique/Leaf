#ifndef _TOKEN_C_
#define _TOKEN_C_

#include <assert.h>
#include <stddef.h>

typedef enum token_type_e {
    LET = 1, CONST, VOID, NULL_TOK, FN, RETURN,
    STRUCT, SUM,
    IF, ELSE, SWITCH, CASE, DEFAULT,
    FOR, WHILE, BREAK, CONTINUE,
    I8, I16, I32, I64,
    U8, U16, U32, U64,
    BOOL,
    F32, F64,
    CHAR, STR,
    PLUS, MINUS, TIMES, DIVIDE, MOD,
    EQUALS, DIFFERENTS, INF, SUP, INF_EQ, SUP_EQ,
    AND, OR, NOT,
    AND_BIT, OR_BIT, NOT_BIT, LEFT_BIT, RIGHT_BIT,
    SEMICOLON, COLON, COMMA, DOT, ARROW,
    LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE,
    ID, LITTERAL
} token_type;

typedef unsigned int token;

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

#endif
