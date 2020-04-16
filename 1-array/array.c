#include "array.h"
#include <stdio.h>

array_t *array_init(int size)
{
	array_t *p;
	p = (array_t *)malloc(sizeof(array_t));
	if (p == NULL) {
		return NULL;
	}
	p->len = 0;
	p->size = size;
	p->p = (int *)calloc(1, size*sizeof(int));
	if (p->p == NULL) {
		free(p);
		return NULL;
	}

	return p;
}

void array_free(array_t *array)
{
	if (array == NULL)
	  return;
	if (array->p != NULL)
	  free(array->p);
	free(array);
}

int array_insert(array_t *array, int value)
{
	int index, len;
	int *src, *dst;
	if (array == NULL && array->len >= array->size)
	  return -1;

	for (index = 0; index < array->len; index++) {
		if (array->p[index] >= value) {
			break;
		}
	}
	//printf("index:%d val:%d\n", index, array->p[index]);

	src = &array->p[array->len];
	dst = &array->p[array->len + 1];
	len = array->len - index + 1;

	while (len--) {
		*dst-- = *src--;
	}

	array->p[index] = value;
	array->len++;

	return 0;
}

int array_len(array_t *array)
{
	if (array != NULL)
	  return array->len;
	return 0;
}

void array_del_val(array_t *array, int value)
{
	int index, len;
	int *src, *dst;

	for (index = 0; index < array->len; index++) {
		if (array->p[index] == value) {
			break;
		}
	}
	if (index >= array->len) {
		printf("not find value\n");	
		return;
	}

	len = array->len - index + 1;
	src = &array->p[index + 1];
	dst = &array->p[index];

	while (len--) {
		*dst++ = *src++;
	}
	array->len--;
}

void array_print(array_t *array)
{
	int i;
	for (i=0; i<array->len; i++) {
		printf("%d ", array->p[i]);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	array_t *p;
	p = array_init(10);
	array_insert(p, 2);
	array_print(p);
	array_insert(p, 5);
	array_print(p);
	array_insert(p, 3);
	array_print(p);
	array_insert(p, 1);
	array_print(p);
	array_insert(p, 4);
	array_print(p);
	array_del_val(p, 3);
	array_print(p);
	array_del_val(p, 6);
	array_print(p);
	array_del_val(p, 5);
	array_print(p);
	array_free(p);
	return 0;
}
