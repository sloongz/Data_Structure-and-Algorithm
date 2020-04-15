#include "array.h"

#include <stdio.h>

array_t *array_create()
{
	array_t *array = NULL;
	array = malloc(sizeof(array_t));
	if (array == NULL) {
		return NULL;
	}
	array->p = NULL;
	array->size = 0;
	array->len = 0;
	array->typesize = 0;
	return array;
}
void array_init(array_t *array, int size, int typesize)
{
	if (array == NULL && size<0 && typesize <=0) {
		return;
	}

	array->size = size;
	array->typesize = typesize;
	array->len = 0;	
	array->p = calloc(1, size*typesize);
	
	if (array->p == NULL) {
		return;
	}
}

void array_free(array_t *array)
{
	if (array = NULL)
		return;
	if (array->p != NULL) {
		free(array->p);
		array->p = NULL;
	}
	free(array);
	array = NULL;
}

//int array_insert(array_t *array, size_t pos, void *const value);
//size_t array_search_val(array_t *array, void *const value);
//void *array_get_index_val(array_t *array, size_t index);
//int array_modify(array_t *array, size_t pos, void *const value);
//size_t array_len(array_t *array);
//void array_del_val(array_t *array, void *const value);
//void array_del_index(array_t *array, size_t index);

void array_print(array_t *array)
{
	int i = 0;
	for (i=0; i<array->len; i++) {
		printf("%d\n", *((int *)array->p + i));
	}
}

int main(int argc, char **argv)
{
	array_t *p;
	
	p = array_create();	
	array_init(p, 20, sizeof(int));		
	array_print(p);

	return 0;
}
