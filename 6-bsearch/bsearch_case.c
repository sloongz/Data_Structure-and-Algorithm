#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int b_search_case1(int *arr, int len, int val)
{
	int mid;
	int low = 0;
	int high = len - 1;

	while (low <= high) {
		mid = low + ((high - low)>>1);
		if (arr[mid] > val) {
			high = mid - 1;		
		} else if (arr[mid] < val) {
			low = mid + 1;
		} else {
			if (mid == 0 || arr[mid - 1] != val) {
				return mid;
			} else {
				high = mid - 1;	
			}
		} 
	}
	return -1;
}

int b_search_case2(int *arr, int len, int val)
{
	int mid;
	int low = 0;
	int high = len - 1;

	while (low <= high) {
		mid = low + ((high - low)>>1);
		if (arr[mid] > val) {
			high = mid - 1;		
		} else if (arr[mid] < val) {
			low = mid + 1;
		} else {
			if (mid == 0 || arr[mid + 1] != val) {
				return mid;
			} else {
				low = mid + 1;	
			}
		} 
	}
	return -1;
}

int b_search_case3(int *arr, int len, int val)
{
	int mid;
	int low = 0;
	int high = len - 1;

	while (low <= high) {
		mid = low + ((high - low)>>1);
		if (arr[mid] >= val) {
			if (mid == 0 || arr[mid-1] < val) {
				return mid;
			} else {
				high = mid - 1;
			}
		} else {
			low = mid + 1;
		}
	}

	return -1;
}

int b_search_case4(int *arr, int len, int val)
{
	int mid;
	int low = 0;
	int high = len - 1;

	while (low <= high) {
		mid = low + ((high - low)>>1);
		if (arr[mid] <= val) {
			if ((mid == (len-1)) || arr[mid+1] > val) {
				return mid;
			} else {
				low = mid + 1;		
			}
		} else {
			high = mid - 1;
		}
	}

	return -1;
}

//变体一：查找第一个值等于给定值的元素
//变体二：查找最后一个值等于给定值的元素
//变体三：查找第一个大于等于给定值的元素
//变体四：查找最后一个小于等于给定值的元素

int main()
{
	int index;
	int a1[] = {1, 3, 4, 5, 6, 8, 8, 8, 11, 18};
	int a2[] = {3, 4, 6, 7, 10};
	index = b_search_case1(a1, sizeof(a1)/sizeof(int), 8);
	if (index == -1) {
		printf("not find\n");
	} else {
		printf("case1: index:%d val:%d\n", index, a1[index]);
	}

	index = b_search_case2(a1, sizeof(a1)/sizeof(int), 8);
	if (index == -1) {
		printf("not find\n");
	} else {
		printf("case2: index:%d val:%d\n", index, a1[index]);
	}

	index = b_search_case3(a2, sizeof(a2)/sizeof(int), 5);
	if (index == -1) {
		printf("not find\n");
	} else {
		printf("case3: index:%d val:%d\n", index, a2[index]);
	}

	index = b_search_case4(a2, sizeof(a2)/sizeof(int), 5);
	if (index == -1) {
		printf("not find\n");
	} else {
		printf("case4: index:%d val:%d\n", index, a2[index]);
	}

	return 0;
}
