#include <stdio.h>
#include <stdlib.h>
#include "list_stack.h"

list_stack_t *list_stack_init()
{
	list_stack_t *pstack = (list_stack_t *)malloc(sizeof(list_stack_t));
	pstack->pos = -1;
	pstack->head = NULL;

	return pstack;
}

void list_stack_free(list_stack_t *stack)
{
	list_node_t *pnode;
	
	if (stack == NULL)
		return;

	while (stack->head != NULL) {
		pnode = stack->head;
		stack->head = pnode->next;
		free(pnode);
	}

	free(stack);
}

void list_stack_dump(list_stack_t *stack)
{
	list_node_t *pnode;

	pnode = stack->head;
	printf("print stack:");
	while (pnode != NULL) {
		printf("%d ", pnode->value);
		pnode = pnode->next;
	}
	printf("\n");
}

int list_stack_push(list_stack_t *stack, int val)
{
	list_node_t *pnew;

	if (stack == NULL)
		return -1;

	pnew = (list_node_t *)malloc(sizeof(list_node_t));
	if (pnew == NULL)
		return -1;

	pnew->value = val;
	pnew->next = stack->head;
	stack->head = pnew;
	stack->pos++;

	return 0;
}

int list_stack_pop(list_stack_t *stack)
{
	int ret;
	list_node_t *p;

	if (stack == NULL)
		return -1;

	p = stack->head;
	if (p == NULL) {
		printf("stack is empty\n");
		return 0;
	}
	ret = p->value;

	stack->head = p->next;
	free(p);
	stack->pos--;
	
	return ret;
}

int list_stack_peek(list_stack_t *stack)
{
	if (stack == NULL)
		return -1;

	return stack->head->value;
}

int main()
{
	list_stack_t *pstack;
	
	pstack = list_stack_init();

	list_stack_dump(pstack);
	list_stack_push(pstack, 1);
	list_stack_push(pstack, 2);
	list_stack_push(pstack, 3);
	list_stack_push(pstack, 4);
	list_stack_push(pstack, 5);
	list_stack_dump(pstack);
	printf("pop: %d\n", list_stack_pop(pstack));
	printf("pop: %d\n", list_stack_pop(pstack));
	list_stack_dump(pstack);
	printf("peek: %d\n", list_stack_peek(pstack));
	list_stack_dump(pstack);

	list_stack_free(pstack);

	return 0;
}
