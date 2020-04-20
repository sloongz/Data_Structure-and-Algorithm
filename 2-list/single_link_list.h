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


link_list_t *list_init(void);
link_list_t *list_add_node_head(link_list_t *list, int val);
link_list_t *list_add_node_tail(link_list_t *list, int val);
link_list_t *list_insert_node(link_list_t *list, int oldval, int val, bool after);
void list_del_node(link_list_t *list, int val);
size_t list_length(link_list_t *list);
void list_release(link_list_t *list);
void list_sort(link_list_t *list);
void list_rewind(link_list_t *list);
void list_print(link_list_t *list);


#endif
