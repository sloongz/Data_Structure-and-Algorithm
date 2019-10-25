#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct array {
	int size;
	int used;
	int *arr;
};

void alloc(struct array *array)
{
	array->arr = (int *)malloc(array->size * sizeof(int));
}

int insert(struct array *array, int elem)
{
	int i;
	
	if (array->used >= array->size) {
		printf("array full\n");
		return -1;
	}

	for (i = 0; i < array->used; i++) {
		if (array->arr[i] > elem)
		  break;
	}

	if (i < array->used)
		memmove(&array->arr[i+1], &array->arr[i], (array->used-i)*sizeof(int));
	
	array->arr[i] = elem;
	array->used++;
	
	return i;
}

int delete(struct array *array, int idx)
{
	if (idx < 0 || idx > array->used) {	
		printf("out of range\n");
		return -1;
	}

	memmove(&array->arr[idx], &array->arr[idx+1], (array->used - idx - 1)*sizeof(int));
	array->used--;

	return 0;
}

int search(struct array *array, int elem)
{
	int i;

	for (i = 0; i < array->used; i++) {
		if (array->arr[i] == elem)
		  return i;
		if (array->arr[i] > elem)
		  return -1;
	}

	return -1;
}


void print(struct array *array)
{
	int i;

	for (i=0; i<array->used; i++) {
		printf("idx[%d]=%d\n", i, *(array->arr+i));
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	struct array ten_int = {10, 0, NULL};
	int idx;

	alloc(&ten_int);
	if (ten_int.arr == NULL) {
		printf("alloc memory fail\n");
		return -1;
	}

	insert(&ten_int, 5);
	insert(&ten_int, 1);
	insert(&ten_int, 8);
	insert(&ten_int, 9);
	insert(&ten_int, 2);
	insert(&ten_int, 6);
	print(&ten_int);

	delete(&ten_int, 0);
	print(&ten_int);

	idx = search(&ten_int, 8);
	printf("8 positon is %d\n", idx);

	return 0;
}
