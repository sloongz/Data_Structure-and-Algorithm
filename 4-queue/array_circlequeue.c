#include <stdio.h>
#include <stdlib.h>
#include "array_circlequeue.h"

array_cirlequeue_t *array_cirlequeue_init(int size)
{
	array_cirlequeue_t *queue;

	queue = (array_cirlequeue_t *)malloc(sizeof(array_cirlequeue_t));
	if (queue == NULL)
		return NULL;
	queue->array = (int *)malloc(sizeof(int)*size);
	if (queue->array == NULL) {
		free(queue);
		return NULL;
	}
	queue->size = size + 1;
	queue->head = 0;
	queue->tail = 0;

	return queue;
}

int array_cirlequeue_free(array_cirlequeue_t *queue)
{
	if (queue == NULL)
		return -1;

	if (queue->array != NULL)
		free(queue->array);

	free(queue);

	return 0;
}
int array_cirlequeue_dequeue(array_cirlequeue_t *queue)
{
	int ret;

	if (queue == NULL)
		return -1;

	if (queue->head == queue->tail) {
		printf("queue empty\n");
		return -1;
	}

	ret = queue->array[queue->head];
	queue->head = (queue->head + 1)%queue->size;

	return ret;
}

int array_cirlequeue_enqueue(array_cirlequeue_t *queue, int val)
{
	if (queue == NULL)
		return -1;

	if (queue->head == (queue->tail+1)%queue->size) {
		printf("queue full\n");
		return 0;
	}

	queue->array[queue->tail] = val;
	queue->tail = (queue->tail + 1)%queue->size;

	return 0;
}


int main()
{
	array_cirlequeue_t *queue;
	queue = array_cirlequeue_init(5);

	array_cirlequeue_enqueue(queue, 1);
	array_cirlequeue_enqueue(queue, 2);
	array_cirlequeue_enqueue(queue, 3);
	array_cirlequeue_enqueue(queue, 4);
	array_cirlequeue_enqueue(queue, 5);
	array_cirlequeue_enqueue(queue, 6);

	printf("enqueue: %d\n", array_cirlequeue_dequeue(queue));
	printf("enqueue: %d\n", array_cirlequeue_dequeue(queue));
	printf("enqueue: %d\n", array_cirlequeue_dequeue(queue));
	printf("enqueue: %d\n", array_cirlequeue_dequeue(queue));
	printf("enqueue: %d\n", array_cirlequeue_dequeue(queue));
	printf("enqueue: %d\n", array_cirlequeue_dequeue(queue));

	array_cirlequeue_free(queue);

	return 0;
}
