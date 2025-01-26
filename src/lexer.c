#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "yeson.h"

token get_string_token(lexer *l);

lexer new_lexer(FILE *fptr) {
	lexer l;
	l.fptr = fptr;
	next_char(&l);
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
	while(l->prev_ch == ' ' || l->prev_ch == '\t' || l->prev_ch == '\r' || l->prev_ch == '\n') {
		next_char(l);
	}
	token t;
	switch(l->prev_ch) {
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
			// Check if digit
			if (isdigit(l->prev_ch) || l->prev_ch == '.' || l->prev_ch == 'e' ||
				l->prev_ch == 'E') {
				/* printf("numzz\n"); */
				char buffer[128] = {0};
				int index = 0;
				while (isdigit(l->prev_ch) || l->prev_ch == '.' || l->prev_ch == 'e' ||
					l->prev_ch == 'E') {
					buffer[index++] = l->prev_ch;
					if (l->ch == ',') {
						break;
					}
					next_char(l);
				}

				/*printf("%c\n", l->prev_ch);*/
				/*printf("NUMZ: %s\n", buffer); */
				if (is_valid_json_numbers(buffer)) {
					t = new_token(NUMBERS, buffer);
					break;
				}

				// Check if boolean
			} else if (l->prev_ch == 't' || l->prev_ch == 'f') {
				char buffer[20] = {0};
				int index = 0;
				/* printf("found em: %c\n", l->prev_ch); */
				while (index < 20 && isalpha(l->prev_ch)) {
					buffer[index++] = l->prev_ch;
					if (l->ch == ',') {
						break;
					}
					next_char(l);
				}

				/*printf("%s\n", buffer);*/
				if (strcmp(buffer, "true") == 0 || strcmp(buffer, "false") == 0) {
					t = new_token(BOOLEAN, buffer);
					break;
				}
			}
			t = new_token(INVALID, "ERROR");
	}

	return t;
}

token get_string_token(lexer *l) {
	token t;
	char buffer[1024] = {0};
	int index = 0;
	int valid_string = 1;
	do {
		if (l->prev_ch == EOF || index > 1023) {
			valid_string = 0;
			break;
		}
		buffer[index++] = l->prev_ch;
		next_char(l);
		if (l->ch == '"' && l->prev_ch == '\\') {
			next_char(l);
			buffer[index] = l->prev_ch;
			index++;
		}
	} while(l->prev_ch != '"');


	if (valid_string) {
		buffer[index++] = '"';
		buffer[index] = '\0';
	} else {
		t = new_token(STRING, "ERROR");
		return t;
	}

	/*printf("Buffer: %s\n", buffer);*/

	if (is_valid_json_string(buffer)) {
		t = new_token(STRING, buffer);
	} else {
		t = new_token(STRING, "ERROR");
	}

	return t;
}

void print_token(token t) {
	printf("(%d, %s)\n", t.tok_type, t.value);
}
