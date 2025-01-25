#include "stack.h"
#include <stdlib.h>

stack_t *new_stack(size_t capacity) {
	stack_t *stack = malloc(sizeof(stack_t));
	if (stack == NULL) {
		return NULL;
	}
	stack->capacity = capacity;
	stack->length = 0;
	stack->data = calloc(capacity, sizeof(state));
	if (stack->data == NULL) {
		free(stack);
		return NULL;
	}
	return stack;
}

void free_stack(stack_t *stack) {
	stack->length = 0;
	stack->capacity = 0;
	free(stack->data);
	free(stack);
}

state peek_stack(stack_t *stack) {
	if (stack->length == 0) {
		return -1;
	}
	return stack->data[stack->length - 1];
}

void push_stack(stack_t *stack, state item) {
	if (stack->length == stack->capacity) {
		state *temp = realloc(stack->data, (2 * stack->capacity) * sizeof(state));
		if (temp == NULL) {
			free(stack->data);
			return;
		}
		stack->data = temp;
	}
	stack->data[stack->length] = item;
	stack->length++;
}

state pop_stack(stack_t *stack) {
	if (stack->length == 0) {
		return -1;
	}

	state data = stack->data[stack->length - 1];
	stack->length--;
	return data;
}
