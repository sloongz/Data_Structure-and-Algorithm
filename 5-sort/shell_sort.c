#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void shell_sort(int *array,int len)
{
	int val;
	int step;
	int k, i, j;

	for (step=len/2; step>0; step=step/2) {
		for (k=0; k<step; k++) {
			for (i=k+step; i<len; i=i+step) {
				val = array[i];
				for (j=i-step; j>=0; j=j-step) {
					if (val < array[j]) {
						array[j+step] = array[j];
					} else {
						break;
					}
				}	
				array[j+step] = val;
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

	shell_sort(array, sizeof(array)/sizeof(int));

	printf("shell sort result:\n");
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		printf("%d\n", array[i]);
	}
}
