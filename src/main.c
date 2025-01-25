#include <stdio.h>
#include "lexer.h"
#include "stack.h"

int main() {
    FILE *fptr;
    char *filename = "yeson-true.txt";
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error reading from file named %s", filename);
        return 1;
    }

	lexer l = new_lexer(fptr);

	stack_t *state_stack = new_stack(10);
	push_stack(state_stack, NEITHER);

	token next_t = { -1, "START" };
	token curr_t = { -1, "START" };

	state curr_state;
	int valid = 1;

	while (1) {
		curr_t = next_t;
		next_t = next_token(&l);
		printf("Current Token: ");
		print_token(curr_t);

		printf("Next Token: ");
		print_token(next_t);

		if (curr_t.tok_type == INVALID) {
			valid = 0;
			break;
		} else if (curr_t.tok_type == END) {
			break;
		} 

		if (curr_t.tok_type == COMMA && (next_t.tok_type == END ||
			next_t.tok_type == R_BRACE || next_t.tok_type == R_SQUARE)) {
			valid = 0;
			break;
		}

		if (curr_t.tok_type == L_BRACE) {
			printf("Lebrace\n");
			push_stack(state_stack, OBJECT);
		} else if (curr_t.tok_type == L_SQUARE) {
			push_stack(state_stack, ARRAY);
		} else if (curr_t.tok_type == R_BRACE || curr_t.tok_type == R_SQUARE) {
			pop_stack(state_stack);
		}

		curr_state = peek_stack(state_stack);

		if (curr_state == OBJECT) {
			if (curr_t.tok_type == L_BRACE) {
				if (next_t.tok_type == R_BRACE || next_t.tok_type == STRING) {
					continue;
				} else {
					valid = 0;
					break;
				}
			}  else if (curr_t.tok_type == COMMA) {
				if (next_t.tok_type != STRING) {
					valid = 0;
					break;
				}
			} else if (curr_t.tok_type == STRING) {
				if (next_t.tok_type == COLON || next_t.tok_type == COMMA 
				|| next_t.tok_type == R_BRACE) {
					continue;
				} else {
					printf("debug\n");
					valid = 0;
					break;
				}
			} else {
				continue;
			}
		}

	}

	if (pop_stack(state_stack) != NEITHER) {
		valid = 0;
	}

	if (valid == 0) {
		printf("INVALID JSON!\n");
	} else {
		printf("VALID JSON!\n");
	}

    
    fclose(fptr);
	free_stack(state_stack);
  
    return 0;
}
