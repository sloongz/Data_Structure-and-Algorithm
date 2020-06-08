#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int b_search(int *arr, int len, int val)
{
	int low = 0;
	int high = len-1;
	int mid;
	
	while (low <= high) {
		
		mid = (low + high)/2;
		
		if (arr[mid] == val) {
			return mid;
		} else if (arr[mid] < val) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}

	return -1;
}

int main(int argc, char **argv)
{
	int arr[] = {1, 3, 8, 10, 20, 40, 60, 80, 100, 200};	
	int index;
	
	index = b_search(arr, sizeof(arr)/sizeof(int), 3);
	printf("index:%d - val:%d\n", index, arr[index]);

	return 0;
}
