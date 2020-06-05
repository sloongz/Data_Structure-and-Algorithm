#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arr_queue {
	int *arr;
	int head;
	int tail;
	int size;
	int num;
} arr_queue_t;

arr_queue_t *queue_init(int size)
{
	arr_queue_t *queue; 
	queue = (arr_queue_t *)malloc(sizeof(arr_queue_t));
	if (queue == NULL) {
		printf("malloc err\n");
		return NULL;
	}

	queue->arr = (int *)malloc(sizeof(int )*size);
	if (queue->arr == NULL) {
		free(queue);
		return NULL;
	}
	memset(queue->arr, 0, size*sizeof(int));

	queue->head = 0;
	queue->tail = 0;
	queue->num = 0;
	queue->size = size;

	return queue;
}

void queue_free(arr_queue_t *queue)
{
	if (queue != NULL) {
		if (queue->arr != NULL) {
			free(queue->arr);
		}
		free(queue);
	}
}

void dump(arr_queue_t *queue)
{
	int i;
	int num = queue->num;
	int head = queue->head;
	int tail = queue->tail;

	if (queue->num == 0) {
		printf("dump queue empty\n");
	} else {
		printf("dump:\n");
		for (;num!=0; head=(head+1)%queue->size, num--) {
			printf("%d ", queue->arr[head]);
		} 
		printf("\n");
	}
}

void tail_cnt_print(arr_queue_t *queue, int cnt)
{
	int i;

	if (queue->num == 0) {
		printf("no val\n");
	} else if (queue->num <= cnt) {
		int head = queue->head;
		printf("tail dump\n");
		for (i=0; i<queue->num; i++) {
			printf("%d ", queue->arr[head]);
			head = (head + 1)%queue->size;
		}
		printf("\n");
	} else {
		int tmp_index = queue->num - cnt + queue->head;
		printf("tail dump\n");
		for (i=0; i<cnt; i++) {
			printf("%d ", queue->arr[tmp_index]);	
			tmp_index = (tmp_index + 1)%queue->size;
		}
		printf("\n");
	}
}

int dequeue(arr_queue_t *queue)
{
	int ret;
	
	if (queue->num == 0) {
		printf("dequeue queue empty\n");
		return -1;
	}

	ret = queue->arr[queue->head];
	queue->head = (queue->head + 1)%queue->size;
	queue->num--;

	return ret;
}

void enqueue(arr_queue_t *queue, int val)
{
	if (queue->num >= queue->size) {
		printf("enqueue queue full\n");	
		queue->head = (queue->head + 1)%queue->size;
	} else {
		queue->num++;
	}

	queue->arr[queue->tail] = val; 
	queue->tail = (queue->tail + 1)%queue->size;
}

int main(int argc, char **argv)
{
	arr_queue_t *queue;
	queue = queue_init(10);

	printf("dequeue %d\n", dequeue(queue));
	enqueue(queue, 1);
	enqueue(queue, 2);
	dump(queue);
	tail_cnt_print(queue, 3);
	enqueue(queue, 3);
	dump(queue);
	tail_cnt_print(queue, 3);
	enqueue(queue, 4);
	enqueue(queue, 5);
	dump(queue);
	tail_cnt_print(queue, 3);
	enqueue(queue, 6);
	enqueue(queue, 7);
	enqueue(queue, 8);
	enqueue(queue, 9);
	enqueue(queue, 10);
	dump(queue);
	tail_cnt_print(queue, 3);
	enqueue(queue, 11);
	dump(queue);
	tail_cnt_print(queue, 3);
	enqueue(queue, 12);
	dump(queue);
	tail_cnt_print(queue, 3);
	printf("dequeue %d\n", dequeue(queue));
	printf("dequeue %d\n", dequeue(queue));
	printf("dequeue %d\n", dequeue(queue));
	printf("dequeue %d\n", dequeue(queue));
	printf("dequeue %d\n", dequeue(queue));
	dump(queue);
	tail_cnt_print(queue, 3);

	queue_free(queue);
	return 0;
}
