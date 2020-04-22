#ifndef _LIST_CIRCLEQUEUE_H_
#define _LIST_CIRCLEQUEUE_H_

typedef struct list_node {
	struct list_node *next;
	int value;
} list_node_t;

typedef struct list_circlequeue {
	list_node_t *head;
	list_node_t *tail;
	int size;
} list_circlequeue_t;

list_circlequeue_t *list_circlequeue_init();
int list_circlequeue_free(list_circlequeue_t *queue);
int list_circlequeue_enqueue(list_circlequeue_t *queue, int val);
int list_circlequeue_dequeue(list_circlequeue_t *queue);
void list_circlequeue_dump(list_circlequeue_t *queue);

#endif //_LIST_CIRCLEQUEUE_H_
