#include "binarysearchtree.h"
#include <stdio.h>
#include <stdlib.h>

bstree_t *bstree_create()
{
	bstree_t *tree;

	tree = (bstree_t *)malloc(sizeof(bstree_t));
	if (!tree)
		return NULL;
	tree->root = NULL;
	tree->size = 0;

	return tree;
}

int bstree_insert(bstree_t *tree, int val)
{
	bstree_node_t *tmp;
	bstree_node_t *node;

	node = (bstree_node_t *)malloc(sizeof(bstree_node_t));
	if (!node)
		return -1;

	node->data = val;
	node->rchild = NULL;
	node->lchild = NULL;

	if (tree->root == NULL) {
		tree->root = node;
		tree->size = 1;
		return 0;
	} else {
		tmp = tree->root;	
		while (tmp != NULL) {
			if (val > tmp->data) {
				if (tmp->rchild == NULL) {
					tmp->rchild = node;
					tree->size++;
					return 0;
				} 
				tmp = tmp->rchild;
			} else {
				if (tmp->lchild == NULL) {
					tmp->lchild = node;
					tree->size++;
					return 0;
				}
				tmp = tmp->lchild;
			}
		}
	}

	return -1;
}

bstree_node_t *bstree_search(bstree_t *tree, int val)
{
	bstree_node_t *tmp;

	tmp = tree->root;

	while (tmp != NULL) {
		if (val > tmp->data) {
			tmp = tmp->rchild;
		} else if (val < tmp->data) {
			tmp = tmp->lchild;
		} else {
			printf("search val:%d\n", tmp->data);
			return tmp;
		}
	}

	return NULL;
}

int compare(int key1, int key2)
{
	return key1 - key2;
}

int bstree_delete(bstree_t *tree, int val)
{
	bstree_node_t *parent_node; //记录的是node的父节点
	bstree_node_t *node; //指向要删除的节点，初始化指向根节点
	bstree_node_t *parent_minnode;
	bstree_node_t *minnode;
	bstree_node_t *tmp;
	int ret;

	node = tree->root;
	while (node != NULL && (ret = compare(val, node->data)) != 0) {
		parent_node = node;
		if (ret > 0) {
			node = node->rchild;
		} else if (ret < 0){
			node = node->lchild;
		}
	}

	//没有找到
	if (node == NULL) {
		return -1;
	}

	printf("delete find val:%d parent:%d\n", node->data, parent_node->data);	

	//要删除的节点有两个子节点
	if (node->rchild != NULL && node->lchild != NULL) {
		minnode = node->rchild; //查找右子树中最小节点
		parent_minnode = minnode;

		while (minnode->lchild != NULL) {
			parent_minnode = minnode;
			minnode = minnode->lchild;			
		}
		node->data = minnode->data;
		printf("min val:%d pmin val:%d\n", minnode->data, parent_minnode->data);
		node = minnode; //将minP的数据替换到node中
		parent_node = parent_minnode; 
	}

	//删除节点是叶子节点或者仅有一个子节点
	if (node->lchild != NULL) {
		tmp = node->lchild;
	} else if (node->rchild != NULL) {
		tmp = node->rchild;
	} else {
		tmp = NULL;
		printf("%d node not have child\n", node->data);
	}

	if (parent_node == NULL) { //删除的是根节点
		tree->root = tmp;
	} else if (parent_node->lchild == node) {
		parent_node->lchild = tmp;		
		printf("parent %d left child is %d\n", parent_node->data, node->data);
	} else {
		parent_node->rchild = tmp;
		printf("parent %d right child is %d\n", parent_node->data, node->data);
	}
	tree->size--;
	free(node);
	node = NULL;

	return 0;
}

void bstree_destory(bstree_t *tree, bstree_node_t *root)
{
	if (root == NULL) {
		return;
	}

	bstree_destory(tree, root->lchild);
	bstree_destory(tree, root->rchild);
	free(root);
	tree->size--;
}


void preorder(bstree_node_t *root)
{
	if (root == NULL)
		return;
	printf("%d ", root->data);
	preorder(root->lchild);
	preorder(root->rchild);
}


void inorder(bstree_node_t *root)
{
	if (root == NULL)
		return;
	inorder(root->lchild);
	printf("%d ", root->data);
	inorder(root->rchild);
}

void postorder(bstree_node_t *root)
{
	if (root == NULL)
		return;
	postorder(root->lchild);
	postorder(root->rchild);
	printf("%d ", root->data);
}

void bstree_dump(bstree_t *tree)
{
	printf("------tree size:%d---------\n", tree->size);
	if (!tree->size)
		return;
	printf("preorder:\n");
	preorder(tree->root);
	//printf("\ninorder:\n");
	//inorder(tree->root);
	//printf("\npostorder:\n");
	//postorder(tree->root);
	printf("\n----end--------------------\n");
}

int main()
{
	bstree_t *tree;

	tree = bstree_create();

	bstree_insert(tree, 50);
	bstree_insert(tree, 60);
	bstree_insert(tree, 40);
	bstree_insert(tree, 30);
	bstree_insert(tree, 45);
	bstree_insert(tree, 70);
	bstree_insert(tree, 65);
	bstree_insert(tree, 25);
	bstree_insert(tree, 80);
	bstree_insert(tree, 46);
	bstree_insert(tree, 47);
	bstree_insert(tree, 42);
	bstree_insert(tree, 41);
	bstree_insert(tree, 43);
#if 0
                 50
             /      \
           40        60
         /  \         \
       30    45        70
      / \      \       / \
     25 42     46     65 80
     /   \      \
   41    43     47
#endif
	bstree_dump(tree);

	bstree_delete(tree, 80);
	bstree_dump(tree);
	bstree_delete(tree, 46);
	bstree_dump(tree);
	bstree_delete(tree, 40);
	bstree_dump(tree);

	bstree_destory(tree, tree->root);

	bstree_dump(tree);
	return 0;
}
