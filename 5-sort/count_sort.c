#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void count_sort(int *array, int len)
{
	int min_val;
	int max_val;
	int i;
	int *arr, *result_arr, size;

	result_arr = malloc(sizeof(int)*len);
	memset(result_arr, 0, sizeof(int)*len);

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

	// 将数据出现的次数存储在arr[]中
	for (i=0; i<len; i++) {
		arr[array[i]-min_val]++;
	}

	// 更改arr[i]。目的是让更改后的arr[i]的值，是该数据在result_arr[]中的位置。
	for (i=1; i<size; i++) {
		arr[i] += arr[i-1];
	}

	//将数据存储到临时数组result_arr[]中
	for (i=len-1; i>=0; i--) {
		result_arr[arr[array[i]-min_val] - 1] = array[i];
		arr[array[i]-min_val]--;
	}

	//将排序好的数据赋值给array[]
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
		array[i] = rand()%1000;
		printf("%d\n", array[i]);
	}

	count_sort(array, sizeof(array)/sizeof(int));

	printf("count sort result:\n");
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		printf("%d\n", array[i]);
	}

	return 0;
}
