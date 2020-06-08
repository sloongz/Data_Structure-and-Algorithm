#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20

void count_sort(int *array, int len)
{
	int min_val;
	int max_val;
	int i, sum;
	int *arr, *result_arr, size;

	min_val = array[0];
	for (i=0; i<len; i++) {
		if (array[i] < min_val) {
			min_val = array[i];
		}
	}

	max_val = array[0];
	for (i=0; i<len; i++) {
		if (array[i] > max_val) {
			max_val = array[i];
		}
	}

	size = max_val - min_val + 1;
	printf("min:%d, max:%d, size:%d\n", min_val, max_val, size);
	arr = (int *)malloc(sizeof(int)*size);
	memset(arr, 0, sizeof(int)*size);

	//input val
	for (i=0; i<len; i++) {
		arr[array[i]-min_val]++;
	}

	//for (i=0; i<size; i++) {
	//	printf("index-%d : val-%d\n", i, arr[i]);
	//}

	//sum
	for (sum=0, i=0; i<size; i++) {
		sum += arr[i];
		arr[i] = sum;
	}

	//for (i=0; i<size; i++) {
	//	printf("-index-%d : val-%d\n", i, arr[i]);
	//}

	result_arr = malloc(sizeof(int)*len);	

	//sort
	for (i=0; i<len; i++) {
		result_arr[arr[array[i]-min_val] - 1] = array[i];
		arr[array[i]-min_val]--;
	}

	//copy
	for (i=0; i<len; i++) {
		array[i] = result_arr[i];
	}

	free(result_arr);
	free(arr);

}


int main()
{
	int array[SIZE];
	int i;

	srand((int)time(NULL));
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		array[i] = rand()%20;
		printf("%d\n", array[i]);
	}

	count_sort(array, sizeof(array)/sizeof(int));

	printf("count sort result:\n");
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		printf("%d\n", array[i]);
	}

	return 0;
}
