#ifndef _LIST_STACK_H_
#define _LIST_STACK_H_

typedef struct list_node {
	struct list_node *next;
	int value;
}list_node_t;

typedef struct list_stack {
	int pos;
	list_node_t *head;
}list_stack_t;

list_stack_t *list_stack_init();
void list_stack_free(list_stack_t *stack);
void list_stack_dump(list_stack_t *stack);
int list_stack_push(list_stack_t *stack, int val);
int list_stack_pop(list_stack_t *stack);
int list_stack_peek(list_stack_t *stack);

#endif
