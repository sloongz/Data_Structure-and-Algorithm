#ifndef __ARRAY_CIRCLEQUEUE_H_
#define __ARRAY_CIRLEQUEUE_H_

typedef struct array_cirlequeue {
	int *array;
	int size;
	int head;
	int tail;
}array_cirlequeue_t;

array_cirlequeue_t *array_cirlequeue_init(int size); 
int array_cirlequeue_free(array_cirlequeue_t *queue);
int array_cirlequeue_dequeue(array_cirlequeue_t *queue);
int array_cirlequeue_enqueue(array_cirlequeue_t *queue, int val);

#endif// __ARRAY_CIRLEQUEUE_H_
