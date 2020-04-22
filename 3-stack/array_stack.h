#ifndef _ARRAY_STACK_H_
#define _ARRAY_STACK_H_

typedef struct array_stack {
	int *array;
	int size;
	int pos;
} array_stack_t;

array_stack_t *stack_init(int size);
int stack_free(array_stack_t *stack);
void stack_dump(array_stack_t *stack);
int stack_push(array_stack_t *stack, int val);
int stack_pop(array_stack_t *stack);
int stack_peek(array_stack_t *stack);

#endif// _ARRAY_STACK_H_

