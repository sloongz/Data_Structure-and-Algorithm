#include <stdio.h>
#include <stdlib.h>
#include "array_stack.h"

array_stack_t *stack_init(int size)
{
	array_stack_t *pstack;

	pstack = (array_stack_t *)malloc(sizeof(array_stack_t));
	if (!pstack)
		return NULL;

	pstack->array = (int *)malloc(sizeof(int)*size);
	pstack->size = size;
	pstack->pos = -1;

	return pstack;
}

int stack_free(array_stack_t *stack)
{
	if (stack == NULL)
		return -1;

	if (stack->array != NULL)
	  free(stack->array);

	free(stack);

	return 0;
}

void stack_dump(array_stack_t *stack)
{
	int i;
	array_stack_t *pstack = stack;
	
	if (pstack == NULL)
	  return;

	printf("printf stack:\n");
	for (i=pstack->pos; i >= 0; i--) {
		printf("%d ", pstack->array[i]);
	}
	if (pstack->pos > 0)
		printf("\n");
}

int stack_push(array_stack_t *stack, int val)
{
	array_stack_t *pstack = stack;

	if (pstack->pos >= pstack->size) {
		printf("stack full\n");
		return -1;
	}

	pstack->pos++;
	pstack->array[pstack->pos] = val;

	return 0;
}

int stack_pop(array_stack_t *stack)
{
	int ret;
	array_stack_t *pstack = stack;

	if (pstack->pos <= 0) {
		printf("stack empty\n");
		return -1;
	}

	ret = pstack->array[pstack->pos];
	pstack->pos--;

	return ret;
}

int stack_peek(array_stack_t *stack)
{
	return stack->array[stack->pos];
}

int main()
{
	array_stack_t *pstack;
	
	pstack = stack_init(10);
	stack_dump(pstack);
	stack_push(pstack, 1);
	stack_push(pstack, 2);
	stack_push(pstack, 3);
	stack_push(pstack, 4);
	stack_push(pstack, 5);
	stack_push(pstack, 6);
	stack_push(pstack, 7);
	stack_dump(pstack);
	printf("pop: %d\n", stack_pop(pstack));
	stack_dump(pstack);
	printf("peek: %d\n", stack_peek(pstack));
	stack_dump(pstack);

	stack_free(pstack);
	return 0;
}
