#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 20

typedef struct arr_list {
	int *arr;
	int size;
	int num;
	int head;
	int tail;
}arr_list_t;

arr_list_t *queue_init(int size)
{
	arr_list_t *queue;
	queue = (arr_list_t *)malloc(sizeof(arr_list_t));
	queue->arr = (int *)malloc(sizeof(int)*size);
	queue->head = 0;
	queue->tail = 0;
	queue->size = size;
	queue->num = 0;
	memset(queue->arr, 0, queue->size);

	return queue;
}

int enqueue(arr_list_t *queue, int val)
{
	if (queue->num >= queue->size) {
		printf("queue full\n");
		return -1;
	}

	queue->arr[queue->tail] = val;
	queue->tail++;
	queue->num++;

	return 0;
}

int dequeue(arr_list_t *queue)
{
	int ret;

	if (queue->num <= 0) {
		printf("queue empty\n");
		return -1;
	}

	ret = queue->arr[queue->head];
	queue->head++;
	queue->num--;

	return ret;
}

void free_queue(arr_list_t *queue)
{
	free(queue->arr);
	free(queue);
}

void bubble_sort(int *array, int len)
{
	int i, j, tmp;
	
	for (i=0; i<len; i++) {
		for (j=0; j<(len-i-1); j++) {
			if (array[j]>array[j+1]) {
				tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
			}
		}
	}
}

void bucket_sort(int *array,int len)
{
	int i, j, k;
	int max_val;
	int min_val;
	int bucket_num;
	int num;

	max_val = array[0];
	for (i=0; i<len; i++) {
		if (array[i] > max_val) {
			max_val = array[i];
		}
	}

	min_val = array[0];
	for (i=0; i<len; i++) {
		if (array[i] < min_val) {
			min_val = array[i];
		}
	}

	bucket_num = (max_val - min_val)/len + 1;
	printf("max:%d min:%d, bucket_num:%d\n", max_val, min_val, bucket_num);

	arr_list_t **bucket_queue = malloc(sizeof(arr_list_t *)*bucket_num);
	for (i=0; i<bucket_num; i++) {
		bucket_queue[i] = queue_init(max_val/bucket_num + 1);	
	}

	//put in bucket
	for (i=0; i<len; i++) {
		num = (array[i]-min_val)/len;
		//printf("enqueue val:%d, num:%d\n", array[i], num);
		enqueue(bucket_queue[num], array[i]);
	}

	//sort
	for (i=0; i<bucket_num; i++) {
		bubble_sort(bucket_queue[i]->arr, bucket_queue[i]->num);	
	}

	//out put
	for (i=0, k=0; i<bucket_num; i++) {
		//printf("bucket:%d, size:%d\n", i, bucket_queue[i]->num);
		num = bucket_queue[i]->num;
		for (j=0; j<num; j++) {
			array[k] = dequeue(bucket_queue[i]);
			//printf("bucket-%d : val-%d\n", i, array[k]);
			k++;
		}
	}
}

int main()
{
	int array[SIZE];
	int i;

	srand((int)time(NULL));
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		array[i] = rand()%100;
		printf("%d\n", array[i]);
	}

	bucket_sort(array, sizeof(array)/sizeof(int));

	printf("bucket sort result:\n");
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		printf("%d\n", array[i]);
	}
}
