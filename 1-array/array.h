#ifndef _ARRAY_H_
#define _ARRAR_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct array {
	int size;
	int len;
	int *p;
} array_t;

array_t *array_init(int size);
int array_insert(array_t *array, int value);
int array_len(array_t *array);
void array_free(array_t *array);
void array_del_val(array_t *array, int value);
void array_print(array_t *array);

#endif 
