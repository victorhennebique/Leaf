#ifndef _TOKEN_H_
#define _TOKEN_H_

typedef enum token_type_e {
    LET, CONST, VOID, FN, RETURN,
    STRUCT, ENUM, UNION,
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
    SEMICOLON, COLON, COMMA, DOT,
    LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE,
    ID, NUMBER, REAL32, REAL64, CHARACTER_L, STRING_L
} token_type;

typedef unsigned int token;

token simple_token(token_type type);

token id_token(unsigned int index);

token number_token(unsigned int index);

token real32_token(unsigned int index);

token real64_token(unsigned int index);

token character_l_token(unsigned int index);

token string_l_token(unsigned int index);

#endif
