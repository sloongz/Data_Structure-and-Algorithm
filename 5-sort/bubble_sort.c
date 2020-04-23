#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void bubble_sort(int *array, int len)
{
	int i, j, tmp;

	for (i=0; i<len; i++) {
		for (j=0; j<(len-i-1); j++) {
			if (array[j] > array[j+1]) {
				tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
			}
		}	
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

	bubble_sort(array, sizeof(array)/sizeof(int));

	printf("bubble sort result:\n");
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		printf("%d\n", array[i]);
	}
}
