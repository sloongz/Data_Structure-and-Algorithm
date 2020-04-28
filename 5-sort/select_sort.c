#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void select_sort(int *array, int len)
{
	int tmp, minpos;
	int i, j;

	for (i=0; i<len; i++) {
		minpos = i;
		for (j=i+1; j<len; j++) {
			if (array[minpos] > array[j]) {
				minpos = j;
			}
		}
		tmp = array[i];
		array[i] = array[minpos];
		array[minpos] = tmp;
	}
}


int main()
{
	int array[SIZE];
	int i;

	srand((int)time(NULL));
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		array[i] = rand()%SIZE;
		printf("%d\n", array[i]);
	}

	select_sort(array, sizeof(array)/sizeof(int));

	printf("select sort result:\n");
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		printf("%d\n", array[i]);
	}
}
