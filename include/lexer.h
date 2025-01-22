#pragma once

#include "token.h"
#include <stdio.h>

typedef struct {
    FILE *fptr;
    char ch;
    char prev_ch;
} lexer;

lexer new_lexer(FILE *fptr);

token new_token(token_type tok_type, char *value);
token next_token(lexer *l);

void print_token(token t);

