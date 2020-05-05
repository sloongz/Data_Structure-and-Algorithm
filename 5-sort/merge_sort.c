#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10

void print(int *arr, int len)
{
	int i;
	for (i=0; i<len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void merge(int *array, int left, int middle, int right)
{
	int *ptmp;
	int i, j, k;

	//printf("left:%d middle:%d right:%d\n", left, middle, right);	

	ptmp = (int *)malloc(sizeof(int)*(right-left+1));
	if (!ptmp)
		return;

	i = left; //left sequence index
	j = middle + 1; //right sequence index
	k = 0; //tmp sequence index
	
	while (i<=middle && j<=right) {
		if (array[i] <= array[j]) {
			ptmp[k++] = array[i++];
		} else {
			ptmp[k++] = array[j++];
		}
	}

	//fill remind left value to tmp array
	while (i<=middle) {
		ptmp[k++] = array[i++];
	}

	//fill remind right value to tmp array
	while (j<=right) {
		ptmp[k++] = array[j++];
	}

	//copy tmp to array
	memcpy(&array[left], ptmp, (right-left+1)*sizeof(int));
	//print(ptmp, right-left+1);
	free(ptmp);
}

void sort(int *array, int left, int right)
{
	int middle;

	if (left >= right)
		return;

	middle = (left + right)/2;

	sort(array, left, middle);
	sort(array, middle+1, right);
	merge(array, left, middle, right);
}

void merge_sort(int *array,int len)
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

	merge_sort(array, sizeof(array)/sizeof(int));

	printf("merge sort result:\n");
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		printf("%d\n", array[i]);
	}
}
