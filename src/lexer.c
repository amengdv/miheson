#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "yeson.h"

token get_string_token(lexer *l);

lexer new_lexer(FILE *fptr) {
    lexer l;
    l.fptr = fptr;

    return l;
}

void next_char(lexer *l) {
    l->prev_ch = l->ch;
    l->ch = fgetc(l->fptr);
}

token new_token(token_type tok_type, char *value) {
    token t;
    t.tok_type = tok_type;
    t.value = value;
    return t;
}

token next_token(lexer *l) {

    next_char(l);
    // SKIP SPACES and UNPRINTABLE CHARS
    while(l->ch == ' ' || l->ch == '\t' || l->ch == '\r' || l->ch == '\n') {
        next_char(l);
    }
    token t;
    switch(l->ch) {
    case '{':
        t = new_token(L_BRACE, "{");
        break;
    case '}':
        t = new_token(R_BRACE, "}");
        break;
    case '[':
        t = new_token(L_SQUARE, "[");
        break;
    case ']':
        t = new_token(R_SQUARE, "]");
        break;
    case EOF:
        t = new_token(END, "EOF");
        break;
    case ',':
        t = new_token(COMMA, ",");
        break;
    case ':':
        t = new_token(COLON, ":");
        break;
    case '"':
        t = get_string_token(l);
        break;

    default:
        if (isdigit(l->ch) || l->ch == '.' || l->ch == 'e' ||
            l->ch == 'E') {
            /* printf("numzz\n"); */
            char buffer[128] = {0};
            int index = 0;
            while (isdigit(l->ch) || l->ch == '.' || l->ch == 'e' ||
            l->ch == 'E') {
                buffer[index++] = l->ch;
                next_char(l);
            }
            /* printf("NUMZ: %s\n", buffer); */
            if (is_valid_json_numbers(buffer)) {
                t = new_token(NUMBERS, buffer);
                break;
            }

        } else if (l->ch == 't' || l->ch == 'f') {
            char buffer[20];
            int index = 0;
            /* printf("found em: %c\n", l->prev_ch); */
            while (index < 20 && isalpha(l->ch)) {
                buffer[index++] = l->ch;
                next_char(l);
            }
                            
            if (strcmp(buffer, "true") == 0 || strcmp(buffer, "false") == 0) {
                t = new_token(BOOLEAN, buffer);
                break;
            }
            printf("%s\n", buffer);
        }
        t = new_token(INVALID, "ERROR");
        
    }

    return t;
}

token get_string_token(lexer *l) {
    char buffer[1024];
    int index = 0;
    do {
        buffer[index++] = l->ch;
        next_char(l);
        if (l->ch == '"' && l->prev_ch == '\\') {
            buffer[index] = l->ch;
            index++;
            next_char(l);
        }
    } while(l->ch != '"');

    
    buffer[index++] = '"';
    buffer[index] = '\0';

    token t;
    if (is_valid_json_string(buffer)) {
        t.tok_type = STRING;
        t.value = buffer;
    } else {
        t.tok_type = INVALID;
        t.value = "ERROR";
    }

    return t;
}

void print_token(token t) {
    printf("(%d, %s)\n", t.tok_type, t.value);
}
