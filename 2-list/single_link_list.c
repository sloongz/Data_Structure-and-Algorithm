#include "single_link_list.h"
#include <stdio.h>

link_list_t *list_init(void)
{
	link_list_t *list = NULL;
	list = malloc(sizeof(*list));
	if (list == NULL)
		return NULL;
	list->head = NULL;
	list->len = 0;

	return list;
}

link_list_t *list_add_node_head(link_list_t *list, int val)
{
	list_node_t *pnode;
	
	pnode = (list_node_t *)malloc(sizeof(*pnode));
	pnode->value = (int *)malloc(sizeof(int)); 
	*pnode->value = val;

	pnode->next = list->head;
	list->head = pnode;
	list->len++;

	return list;
}

link_list_t *list_add_node_tail(link_list_t *list, int val)
{
	list_node_t *pnode;
	list_node_t *p;
	list_node_t *pre;
	
	pnode = (list_node_t *)malloc(sizeof(*pnode));
	pnode->value = (int *)malloc(sizeof(int)); 
	*pnode->value = val;
	
	p = list->head;
	while (p != NULL) {
		pre = p;
		p = p->next;
	}
	pre->next = pnode;

	return list;
}

link_list_t *list_insert_node(link_list_t *list, int oldval, int val, bool after)
{
	return list;
}

void list_del_node(link_list_t *list, int val)
{
	list_node_t *p;
	list_node_t *pre;
	list_node_t *tmp;
	p = list->head;

	if (list == NULL)
		return;

	while (p != NULL) {
	}
}

size_t list_length(link_list_t *list)
{
	if (list == NULL)
	  return 0;
	return list->len;
}

void list_release(link_list_t *list)
{
	list_node_t *pnode;

	if (list == NULL)
		return;

	while (list->head != NULL) {
		pnode = list->head;
		list->head = pnode->next;
		free(pnode->value);
		free(pnode);
	}

	free(list);
}

void list_print(link_list_t *list)
{
	list_node_t *pnode;
	pnode = list->head;

	while (pnode != NULL) {
		if (pnode->value != NULL)
			printf("%d\n", *pnode->value);
		pnode = pnode->next;
	}
}

int main(int argc, char **argv)
{
	link_list_t *plist;

	plist = list_init();

	list_add_node_head(plist, 2);
	list_add_node_head(plist, 4);
	list_add_node_tail(plist, 1);
	list_add_node_tail(plist, 3);
	list_print(plist);

	list_release(plist);

	return 0;
}
