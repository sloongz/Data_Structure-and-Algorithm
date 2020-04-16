#ifndef _SINGLE_LINK_H_
#define _SINGLE_LINK_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct list_node {
	struct list_node *next;
	int *value;
} list_node_t;

typedef struct link_list {
	list_node_t *head;
	size_t len;
} link_list_t;



#endif
