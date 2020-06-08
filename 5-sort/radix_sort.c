#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10

void count_sort(int *a, int len, int exp)
{
	int i, buckets[10] = {0};
	// 存储"被排序数据"的临时数组
	int *output = malloc(sizeof(int)*len);

	// 将数据出现的次数存储在buckets[]中
	for (i = 0; i < len; i++) {
		buckets[ (a[i]/exp)%10 ]++;
	}

	// 更改buckets[i]。目的是让更改后的buckets[i]的值，是该数据在output[]中的位置。
	for (i = 1; i < 10; i++) {
		buckets[i] += buckets[i - 1];
	}

	// 将数据存储到临时数组output[]中
	for (i = len - 1; i >= 0; i--) {
		output[buckets[ (a[i]/exp)%10 ] - 1] = a[i];
		buckets[ (a[i]/exp)%10 ]--;
	}

	// 将排序好的数据赋值给a[]
	for (i = 0; i < len; i++) {
		a[i] = output[i];
	}

	free(output);
}

void radix_sort(int *array, int len)
{
	int exp;
	int max_val;
	int i;

	max_val = array[0];
	for (i=0 ; i<len; i++) {
		if (max_val < array[i]) {
			max_val = array[i];
		}
	}
	printf("max_val:%d\n", max_val);

	for (exp=1; max_val/exp>0; exp*=10) {
		count_sort(array, len, exp);
	}
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

	radix_sort(array, sizeof(array)/sizeof(int));

	printf("radix sort result:\n");
	for (i=0; i<sizeof(array)/sizeof(int); i++) {
		printf("%d\n", array[i]);
	}
}
