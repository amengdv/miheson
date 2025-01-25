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

	stack_t *state_stack = new_stack(10);
	push_stack(state_stack, NEITHER);
	int valid = 1;
    lexer l = new_lexer(fptr);
	token t;
	state curr_state;
	while ((t = next_token(&l)).tok_type != END) {
		if (t.tok_type == INVALID) {
			valid = 0;
			break;
		}
		if (t.tok_type == L_BRACE) {
			push_stack(state_stack, OBJECT);
		} else if (t.tok_type == L_SQUARE) {
			push_stack(state_stack, ARRAY);
		} else if (t.tok_type == R_BRACE || t.tok_type == R_SQUARE) {
			pop_stack(state_stack);
		}

		curr_state = peek_stack(state_stack);

		// IF CURRENT STATE IS OBJECT
		if (curr_state == OBJECT) {
			token kv_pairs[3] = {0};
			int wrong_in_loop = 0;
			for (int i = 0; i < 3; ++i) {
				printf("%d\n", i);
				kv_pairs[i] = next_token(&l);
				print_token(kv_pairs[i]);
				if (kv_pairs[i].tok_type == INVALID) {
					valid = 0;
					wrong_in_loop = 1;
					break;
				}
				if (kv_pairs[i].tok_type == R_BRACE && i == 0) {
					valid = 1;
					wrong_in_loop = 1;
					break;
				} else if (kv_pairs[i].tok_type == R_BRACE && i != 0) {
					valid = 0;
					wrong_in_loop = 1;
					break;
				}
				if (kv_pairs[i].tok_type == END) {
					valid = 0;
					wrong_in_loop = 1;
					break;
				} 
			}

			if (wrong_in_loop == 1) break;

			if (kv_pairs[0].tok_type!= STRING && kv_pairs[1].tok_type != COLON
				&& kv_pairs[2].tok_type != STRING) {
				valid = 0;
				break;
			}
		}

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


