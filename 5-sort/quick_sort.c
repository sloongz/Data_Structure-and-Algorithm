#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void print(int *arr, int len)
{
	int i;
	printf("debug:");
	for (i=0; i<len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

//find the point of division
int partition(int *array, int left, int right)
{
	int min_index, max_index;
	int podiv = right;

	for (min_index=left, max_index=left; max_index<podiv; max_index++) {
		if (array[max_index] < array[podiv]) {
			if (min_index != max_index) {
				swap(&array[min_index], &array[max_index]);
			}
			min_index++;
		}
	}
	swap(&array[min_index], &array[podiv]);
	print(array, 10);
	return min_index;
}

void sort(int *array, int left, int right)
{
	int partition_index;

	if (left >= right)
	  return;

	partition_index = partition(array, left, right);
	sort(array, left, partition_index-1);
	sort(array, partition_index+1, right);
}

void quick_sort(int *array,int len)
{
	sort(array, 0, len-1);
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

	quick_sort(array, sizeof(array)/sizeof(int));

	printf("quick sort result:\n");
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		printf("%d\n", array[i]);
	}
}
