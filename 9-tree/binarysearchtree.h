#ifndef _BSTREE_H_
#define _BSTREE_H_

typedef struct bstree_node {
	int data;
	struct bstree_node *rchild;
	struct bstree_node *lchild;
} bstree_node_t;

typedef struct bstree {
	struct bstree_node *root;
	int size;
} bstree_t;

#endif

