#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//http://www.cppblog.com/mysileng/archive/2013/04/06/199159.html
//https://github.com/wangzheng0822/algo/blob/master/c-cpp/17_skiplist/skiplist_c/skiplist.c

//例子:
//0 ----------------> 9
//0 ------> 5 ------> 9
//0 -->3--> 5--> 7--> 9

typedef struct node {
	int val;				//节点值
	int max_level;			//该节点最大层数
	struct node *next[1];//各层链表
} node_t;

typedef struct skip_list {
	int level;		//跳表的层数
	node_t *head;	//跳表的头节点
} skip_list_t;


//创建节点， 这个节点有几层:max_level 节点值:value
node_t *create_node(int max_level, int value)
{
	node_t *pnode = malloc(sizeof(node_t) + max_level*sizeof(node_t *)); //node_t + *next[max_level];
	pnode->val = value;
	pnode->max_level = max_level;

	return pnode;
}

skip_list_t *skip_list_create(int max_level)
{
	skip_list_t *slist;
	int i;

	slist = (skip_list_t *)malloc(sizeof(skip_list_t));
	if (slist == NULL) {
		printf("err\n");
		return 0;
	}

	slist->level = max_level;
	slist->head = create_node(max_level, 0); //创建头结点， 头结点的值是0, 头结点占所有层
	for (i=0; i<max_level; i++) {
		slist->head->next[i] = NULL;
	}

	return slist;
}

int random_level(int max_level)
{
	int ret = 1;
	
	while (ret < max_level && rand()%2) {
		ret++;
	}

	return ret;
}

//插入位置和插入高度
int insert(skip_list_t *sklist, int value)
{
	int i;
	int level = 0;
	node_t *new = NULL;
	node_t *pnode = NULL;
	node_t *prev = NULL;
	node_t **update;

	//申请update空间用于保存每层的指针
	update = (node_t **)malloc(sizeof(node_t *) * sklist->level);

	//从最高层往下查找需要插入的位置
	prev = sklist->head;
	for (i=sklist->level-1; i>=0; i--) {
		while ( (pnode=prev->next[i]) !=NULL && pnode->val < value ) {
			prev = pnode;
		}
		update[i] = prev;
	}

	//获取节点的最大层数
	level = random_level(sklist->level);
	//printf("insert max level:%d\n", level);
	
	//创建节点
	new = create_node(sklist->level, value);

	//逐层更新节点的指针
	for (i=0; i<level; i++) {
		new->next[i] = update[i]->next[i];
		update[i]->next[i] = new;
	}

	return 0;
}

//删除
int delete(skip_list_t *sklist, int value)
{
	node_t *pnode;
	node_t **update;
	node_t *prev = NULL;
	int i;

	update = (node_t **)malloc(sizeof(node_t *)*sklist->level);

	prev = sklist->head;
	for (i=sklist->level-1; i>0; i--) {
		while ( (pnode=prev->next[i]) != NULL && pnode->val < value) {
			prev = pnode;
		}
		update[i] = prev;
	}

	if (pnode!=NULL && pnode->val == value) {
		printf("\n");	
	} else {
		printf("can not find value:%d\n", value);
		return -1;
	}

	return 0;
}

//销毁
void destory(skip_list_t *sklist)
{
	node_t *pnode;
	
	while (sklist->head->next[0] != NULL) {
		pnode = sklist->head;
		sklist->head = sklist->head->next[0];
		free(pnode);
	}

	free(sklist->head);
	free(sklist);
}

void dump_skip_list(skip_list_t *slist)
{
	int i;
	node_t *pnode;

	for (i=slist->level-1; i>=0; i--) {
		printf("--l:%d--------\n", i);
		pnode = slist->head->next[i];
		while (pnode != NULL) {
			printf("%d\t", pnode->val);
			pnode = pnode->next[i];
		}
		printf("\n");
	}
}

int main()
{
	int i;
	skip_list_t *sklist;
	srand((int)time(NULL));

	sklist = skip_list_create(5);

	for (i=1; i<10; i++) {
		insert(sklist, i*2);	
	}
	
	dump_skip_list(sklist);

	destory(sklist);

	return 0;
}
