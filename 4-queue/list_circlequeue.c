#include <stdio.h>
#include <stdlib.h>
#include "list_circlequeue.h"

list_circlequeue_t *list_circlequeue_init()
{
	list_circlequeue_t *queue;

	queue = (list_circlequeue_t *)malloc(sizeof(list_circlequeue_t));
	if (queue == NULL)
		return NULL;

	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;

	return queue;
}

int list_circlequeue_free(list_circlequeue_t *queue)
{
	list_node_t *pnode; 

	if (queue == NULL)
		return -1;

	while (queue->head != NULL) {
		pnode = queue->head;
		queue->head = pnode->next;
		free(pnode);
	}

	free(queue);

	return 0;
}

int list_circlequeue_enqueue(list_circlequeue_t *queue, int val)
{
	list_node_t *pnew;

	pnew = (list_node_t *)malloc(sizeof(list_node_t));
	if (pnew == NULL)
		return -1;
	pnew->value = val;
	pnew->next = NULL;

	if (queue->head == NULL) {
		queue->head = pnew;
	} else {
		queue->tail->next = pnew;
	}

	queue->tail = pnew;
	queue->size++;

	return 0;
}

int list_circlequeue_dequeue(list_circlequeue_t *queue)
{
	int ret;
	list_node_t *p;

	if (queue == NULL)
		return -1;

	p = queue->head;
	queue->head = p->next;
	ret = p->value;
	free(p);

	queue->size--;

	return ret;
}

void list_circlequeue_dump(list_circlequeue_t *queue)
{
	list_node_t *p;

	printf("dump queue:");
	p = queue->head;
	while (p != NULL) {
		printf("%d ", p->value);
		p = p->next;
	}
	printf("\n");
}

int main()
{
	list_circlequeue_t *queue;

	queue = list_circlequeue_init();
	list_circlequeue_enqueue(queue, 1);
	list_circlequeue_enqueue(queue, 2);
	list_circlequeue_enqueue(queue, 3);
	list_circlequeue_enqueue(queue, 4);
	list_circlequeue_enqueue(queue, 5);

	list_circlequeue_dump(queue);

	printf("dequeue:%d, size:%d\n", list_circlequeue_dequeue(queue), queue->size);
	printf("dequeue:%d\n", list_circlequeue_dequeue(queue));
	printf("dequeue:%d\n", list_circlequeue_dequeue(queue));
	list_circlequeue_dump(queue);
	printf("dequeue:%d\n", list_circlequeue_dequeue(queue));
	printf("dequeue:%d\n", list_circlequeue_dequeue(queue));
	list_circlequeue_dump(queue);

	list_circlequeue_free(queue);
	return 0;
}
