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
	list_node_t *pnew;
	
	pnew = (list_node_t *)malloc(sizeof(*pnew));
	pnew->value = (int *)malloc(sizeof(int)); 
	*pnew->value = val;

	pnew->next = list->head;
	list->head = pnew;
	list->len++;

	return list;
}

link_list_t *list_add_node_tail(link_list_t *list, int val)
{
	list_node_t *pnew;
	list_node_t *p;
	list_node_t *pre;
	
	pnew = (list_node_t *)malloc(sizeof(*pnew));
	pnew->value = (int *)malloc(sizeof(int)); 
	*pnew->value = val;
	
	p = list->head;
	while (p != NULL) {
		pre = p;
		p = p->next;
	}
	pre->next = pnew;

	return list;
}

link_list_t *list_insert_node(link_list_t *list, int oldval, int val, bool after)
{
	list_node_t *cur;
	list_node_t *pre;
	list_node_t *pnew;

	pnew = (list_node_t *)malloc(sizeof(list_node_t));
	pnew->value = (int *)malloc(sizeof(int));
	*pnew->value = val;

	cur = list->head;
	pre = list->head;
	if (cur == NULL) {
		list->head = pnew;
		list->len = 1;
		return list;
	}

	while (cur != NULL && *cur->value != oldval) {
		pre = cur;
		cur = cur->next;
	}
	
	//printf("### pre:%d cur:%d\n", *pre->value, *cur->value);
	if (after == true) {
		pnew->next = cur->next;
		cur->next = pnew;
	} else {
		pre->next = pnew;
		pnew->next = cur;
			
	}

	return list;
}

void list_del_node(link_list_t *list, int val)
{
	list_node_t *cur;
	list_node_t *pre;

	if (list == NULL)
		return;

	cur = list->head;
	pre = list->head;

	while (cur != NULL && *cur->value !=val) {
		pre = cur;
		cur = cur->next;
	}

	if (cur == NULL) {
		printf("not find value in the list\n");
		return;
	}

	if (pre == list->head && *pre->value == val) {
		list->head = pre->next;
	} else {
		pre->next = cur->next;
		pre = cur;
	}

	list->len--;
	free(pre->value);
	free(pre);
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


static void swap(list_node_t *p, list_node_t *q)
{
	int value;
	
	value = *p->value;
	*p->value = *q->value;
	*q->value = value;
}

void list_sort(link_list_t *list)
{
	list_node_t *p;
	list_node_t *q;
	
	if (list->head == NULL && list->head->next == NULL)
		return;

	for (p = list->head; p != NULL; p = p->next) {
		for (q = p->next; q != NULL; q = q->next) {
			if (*q->value > *p->value)
				swap(q, p);				
		}
	}

}

void list_rewind(link_list_t *list)
{
	list_node_t *pre = NULL;
	list_node_t *phead = list->head;
	list_node_t *pnext;

	while (phead != NULL) {
		pnext = phead->next;
		phead->next = pre;
		pre = phead;
		phead = pnext;
	}
	list->head = pre;
}

void list_print(link_list_t *list)
{
	list_node_t *pnode;
	pnode = list->head;

	printf("print list:\n");
	while (pnode != NULL) {
		if (pnode->value != NULL)
			printf("%d ", *pnode->value);
		pnode = pnode->next;
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	link_list_t *plist;

	plist = list_init();

	list_print(plist);
	list_insert_node(plist, 1, 10, true);
	list_print(plist);
	list_add_node_head(plist, 5);
	list_add_node_head(plist, 2);
	list_add_node_head(plist, 4);
	list_add_node_tail(plist, 1);
	list_add_node_tail(plist, 3);
	list_print(plist);
	list_insert_node(plist, 2, 11, true);
	list_print(plist);
	list_insert_node(plist, 2, 9, false);
	list_print(plist);
	printf("sort:\n");
	list_sort(plist);
	list_print(plist);
	list_rewind(plist);
	list_print(plist);	
	list_del_node(plist, 8);
	list_print(plist);
	list_del_node(plist, 4);
	list_print(plist);
	list_del_node(plist, 3);
	list_print(plist);
	list_del_node(plist, 5);
	list_print(plist);

	list_release(plist);

	return 0;
}
