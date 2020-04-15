#ifndef _ARRAY_H_
#define _ARRAR_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct array {
	size_t size;
	size_t len;
	size_t typesize;
	void *p;
} array_t;

array_t *array_create();
void array_init(array_t *array, int size, int typesize);
int array_insert(array_t *array, size_t pos, void *const value);
size_t array_search_val(array_t *array, void *const value);
void *array_get_index_val(array_t *array, size_t index);
int array_modify(array_t *array, size_t pos, void *const value);
size_t array_len(array_t *array);
void array_free(array_t *array);
void array_del_val(array_t *array, void *const value);
void array_del_index(array_t *array, size_t index);
void array_print(array_t *array);

#endif 
