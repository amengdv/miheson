#pragma once

#include <stdio.h>

typedef enum {
	OBJECT,
	ARRAY,
	NEITHER
} state;

typedef struct Stack {
	size_t length;
	size_t capacity;
	state *data;
} stack_t;

// Return pointer since it has a dynamically allocated members
// Avoid shallow copy (e.g Double Free Errors and Memory Leaks
stack_t *new_stack(size_t);
void free_stack(stack_t *);
void push_stack(stack_t *, state);
state pop_stack(stack_t *);
