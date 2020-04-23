#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void insert_sort(int *array, int len)
{
	int val;
	int i, j;

	for (i=1; i<len; i++) {
		val = array[i];
		for (j=i-1; j>=0; j--) {
			if (val < array[j]) {
				array[j+1] = array[j];
			} else {
				break;
			}	
		}
		//printf("j:%d a[%d]:%d\n", j, j+1, array[j+1]);
		array[j+1] = val;
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

	insert_sort(array, sizeof(array)/sizeof(int));

	printf("insert sort result:\n");
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		printf("%d\n", array[i]);
	}
}
