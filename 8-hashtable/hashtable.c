#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//参考
//linux-3.4/security/selinux/ss/hashtab.h
//linux-3.4/security/selinux/ss/hashtab.c

//例子：
//0 hash_value(key0)=0  
//1 hash_value(key1)=1 -> hash_value(keyx)=1 -> hash_value(keyy)=1
//2 hash_value(key2)=2
//3
//4 hash_value(key4)=4
//5 hash_value(key5)=5
//6
//7
//8
//9 hash_value(key9)=9

#define HASHTAB_MAX_NODES   0xffffffff

struct hashtab_node {
	void *key;
	void *datum;
	struct hashtab_node *next;
};

struct hashtab {
	struct hashtab_node **htable; /* hash table */
	int size; /* number of slots in hash table */
	int nel; /* number of elements in hash table */
	int (*hash_value)(struct hashtab *h, const void *key);
		/* hash function */
	int (*keycmp)(struct hashtab *h, const void *key1, const void *key2/*, int size*/);
		/* key comparison function */	
};

struct hashtab *hashtab_create(int (*hash_value)(struct hashtab *h, const void *key), 
			int (*keycmp)(struct hashtab *h, const void *key1, const void *key2/*, int size*/),
			int size);
int hashtab_insert(struct hashtab *h, void *key, void *d);
void *hashtab_search(struct hashtab *h, const void *key);
int hashtab_delete(struct hashtab *h, void *key);
void hashtab_destroy(struct hashtab *h);


int simple_hash_value(const char *str)
{
	unsigned int hash = 0;
	unsigned int seed = 131;

	while(*str) {
		hash = hash*seed + *str++;
	}

	return hash & (0x7FFFFFFF);
}

int shash_value(struct hashtab *h, const void *key)
{
	return (simple_hash_value((const char *)key) % h->size);
}

int key_cmpare(struct hashtab *h, const void *key1, const void *key2/*, int size*/)
{
	return strcmp((const char *)key1, (const char *)key2);
}

struct hashtab *hashtab_create(int (*hash_value)(struct hashtab *h, const void *key), 
				int (*keycmp)(struct hashtab *h, const void *key1, const void *key2/*, int size*/),
				int size)
{
	struct hashtab *p;
	int i;
	
	p = (struct hashtab *)malloc(sizeof(struct hashtab));
	if (p == NULL)
		return p;

	p->size = size;
	p->nel = 0;
	p->hash_value = hash_value;
	p->keycmp = keycmp;

	p->htable = (struct hashtab_node **)malloc(sizeof(struct hashtab_node *) * size);
	if (p->htable == NULL) {
		free(p);
		return NULL;
	}

	for (i=0; i<size; i++) {
		p->htable[i] = NULL;	
	}

	return p;
}

int hashtab_insert(struct hashtab *h, void *key, void *d)
{
	int hvalue;
	struct hashtab_node *cur = NULL;
	struct hashtab_node *prev = NULL;
	struct hashtab_node *new = NULL;

	if (!h || h->nel >= HASHTAB_MAX_NODES)
		return -1;

	hvalue = h->hash_value(h, key);
	cur = h->htable[hvalue];
	printf("hvalue:%d, key:%s\n", hvalue, (char *)key);

	//如果哈希表的位置是空跳过
	//如果哈希表的位置不是空，找到哈希表的位置对应的链表中的位置
	while (cur != NULL && h->keycmp(h, key, cur->key) > 0) {
		prev = cur;
		cur = cur->next;
	}

	//找到的这个位置的key是重复的 就不用插入了
	if (cur != NULL && h->keycmp(h, key, cur->key) == 0) {
		printf("repeat key:%s\n", (char *)key);
		return -1;
	}

	//在连表中建立这个node 把key存到这个node中
	new = (struct hashtab_node *)malloc(sizeof(struct hashtab_node));
	new->key = key;
	new->datum = d;
	new->next = NULL;

	if (prev == NULL) {
		printf("new value\n");
		h->htable[hvalue] = new;
	} else {
		printf("old value\n");
		new->next = prev->next;
		prev->next = new;
	}

	h->nel++;

	return 0;
}


int hashtab_delete(struct hashtab *h, void *key)
{
	struct hashtab_node *cur = NULL;
	struct hashtab_node *prev = NULL;
	struct hashtab_node *pnode = NULL;
	int hvalue;

	hvalue = h->hash_value(h, key);
	cur = h->htable[hvalue]; 

	while (cur != NULL && h->keycmp(h, key, cur->key) > 0) {
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL) {
		printf("hashtab not this key:%s, value:%d\n", (char *)key, hvalue);	
		return -1;
	}
		
	if (h->keycmp(h, key, cur->key) == 0) {
		printf("find value:%s\n", (char *)key);
		if (!prev) { //是哈希表节点 链表的头节点
			pnode = cur;
			h->htable[hvalue] = NULL;
			free(pnode);
		} else { //不是头节点
			pnode = cur;
			prev->next = cur->next;
			free(pnode);
		}
		return 0;
	}

	printf("not find this key:%s, value:%d\n", (char *)key, hvalue);
	return -1;
}


void *hashtab_search(struct hashtab *h, const void *key)
{
	struct hashtab_node *cur = NULL;
	int hvalue;

	printf("we want to search key:%s\n", (char *)key);

	hvalue = h->hash_value(h, key);	
	cur = h->htable[hvalue];

	while (cur != NULL && h->keycmp(h, key, cur->key) > 0) {
		cur = cur->next;
	}

	if (cur == NULL) {
		printf("not search value:%d NULL\n", hvalue);
		return NULL;
	}

	if (h->keycmp(h, key, cur->key) == 0) {
		printf("search value:%d, key:%s\n", hvalue, (char *)cur->key);
		return cur;
	}
	
	printf("not search value:%d NULL\n", hvalue);
	return NULL;
}

void hashtab_destroy(struct hashtab *h)
{
	int i;
	struct hashtab_node *cur, *tmp;

	for (i=0; i<h->size; i++) {
		cur = h->htable[i];
		while (cur) {
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
		h->htable[i] = NULL;
	}

	free(h->htable);
	h->htable = NULL;

	free(h);
}

void hashtab_dump(struct hashtab *h)
{
	struct hashtab_node *cur;
	int i;

	printf("dump-------------\n");
	for (i=0; i<h->size; i++) {
		cur = h->htable[i];
		if (cur == NULL) {
			printf("value %d NULL\n", i);
		}
		while (cur != NULL) {
			printf("value %d key %s\n", i, (char *)cur->key);
			cur = cur->next;
		}
	} 
}

int main()
{
	char *strs[] = {
		"hello",
		"good",
		"xxxxsss",
		"yyysssssssssy",
		"worldworld",
		"hello",
		"5678",
		"ssssssss",
		"xxxxxxxx",
	};

	struct hashtab *h = NULL;
	int i;

	h = hashtab_create(shash_value, key_cmpare, 10);

	for (i=0; i<sizeof(strs)/sizeof(char *); i++) {
		hashtab_insert(h, strs[i], NULL);
	}

	hashtab_dump(h);

	hashtab_delete(h, "hello");
	hashtab_delete(h, "fake value");
	hashtab_delete(h, "xxxxxxxx");

	hashtab_dump(h);

	hashtab_insert(h, strs[8], NULL);
	hashtab_insert(h, "fake value", NULL);
	hashtab_insert(h, "hello", NULL);
	hashtab_search(h, "xxxxxxxx");

	hashtab_dump(h);

	hashtab_destroy(h);

	return 0;
}
