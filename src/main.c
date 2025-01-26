#include <stdio.h>
#include "lexer.h"
#include "stack.h"

void expect_key_values(lexer *l, token *curr_t, token *next_t, int *valid, stack_t *stack);
void parse(lexer *l, stack_t *stack, token *curr_t, token *next_t, int *valid);

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

	token curr_t = { -1, "START" };
	token next_t = next_token(&l);
	int valid = 1;

	parse(&l, state_stack, &curr_t, &next_t, &valid);
	
	state last = pop_stack(state_stack);
	if (last != NEITHER && state_stack->length > 0) {
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

void expect_key_values(lexer *l, token *curr_t, token *next_t, int *valid, stack_t *stack) {
	if ((curr_t->tok_type == L_BRACE && next_t->tok_type == R_BRACE) || curr_t->tok_type == R_BRACE) {
		pop_stack(stack);
		state latest = peek_stack(stack);
		if (latest == OBJECT) {
			*curr_t = *next_t;
			*next_t = next_token(l);
			expect_key_values(l, curr_t, next_t, valid, stack);
		}
		return;
	}

	if (curr_t->tok_type == COMMA && (next_t->tok_type == R_BRACE || next_t->tok_type == END)) {
		*valid = 0;
		return;
	}

	print_token(*curr_t);
	print_token(*next_t);
	printf("\n");

	int valid_key_1 = (curr_t->tok_type == L_BRACE && next_t->tok_type == STRING);
	int valid_key_2 = (curr_t->tok_type == STRING && next_t->tok_type == COLON);
	int valid_key_3 = (curr_t->tok_type == COMMA && next_t->tok_type == STRING);

	int valid_value_1 = (curr_t->tok_type == COLON && (next_t->tok_type != INVALID
		|| next_t->tok_type != R_BRACE || next_t->tok_type != COMMA
		|| next_t->tok_type != R_SQUARE));
	int valid_value_2 = ((curr_t->tok_type == STRING || curr_t->tok_type == NUMBERS || curr_t->tok_type == BOOLEAN)
			&& (next_t->tok_type == COMMA || next_t->tok_type == R_BRACE));
	int start_of_object = curr_t->tok_type == L_BRACE;
	int nested_object = (curr_t->tok_type == COLON && next_t->tok_type == L_BRACE);

	/*printf("bool: %d\n", (valid_key_1 || valid_key_2 || valid_key_3*/
	/*	|| valid_value_1 || valid_value_2 || start_of_object));*/

	if (valid_key_1 || valid_key_2 || valid_key_3
		|| valid_value_1 || valid_value_2 || start_of_object) {
		if (nested_object) {
			push_stack(stack, OBJECT);
		}
		*curr_t = *next_t;
		*next_t = next_token(l);
		expect_key_values(l, curr_t, next_t, valid, stack);
	} else {
		*valid = 0;
		return;
	}

	/*else if (curr_t->tok_type == L_SQUARE) {*/
	/*	// parse array*/
	/*} */
}

void parse(lexer *l, stack_t *stack, token *curr_t, token *next_t, int *valid) {
	print_token(*curr_t);
	if (curr_t->tok_type == INVALID) {
		*valid = 0;
		return;
	}
	if (curr_t->tok_type == L_BRACE) {
		push_stack(stack, OBJECT);
	}
	if (peek_stack(stack) == NEITHER && (curr_t->tok_type != INVALID && curr_t->tok_type != -1) && next_t->tok_type != END) {
		*valid = 0;
		return;
	}
	if (curr_t->tok_type == COMMA && peek_stack(stack) == NEITHER) {
		*valid = 0;
		return;
	}

	if (curr_t->tok_type == END) {
		return;
	}

	state curr_state = peek_stack(stack);
	
	if (curr_state == OBJECT) {
		expect_key_values(l, curr_t, next_t, valid, stack);
	}

	*curr_t = *next_t;
	*next_t = next_token(l);
	parse(l, stack, curr_t, next_t, valid);
}

