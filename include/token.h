#pragma once

typedef enum {
    // { }
    L_BRACE,
    R_BRACE,

    // [ ]
    L_SQUARE,
    R_SQUARE,

    // ,
    COMMA,

    // :p
    COLON,

    STRING,
    NUMBERS,

    END,
    INVALID
    
} token_type;

typedef struct {
    token_type tok_type;
    char *value;
} token;
