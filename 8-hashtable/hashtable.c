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
	struct hashtab_node_t **htable; /* hash table */
	int size; /* number of slots in hash table */
	int nel; /* number of elements in hash table */
	int (*hash_value)(struct hashtab *h, const void *key);
		/* hash function */
	int (*keycmp)(struct hashtab *h, const void *key1, const void *key2);
		/* key comparison function */	
};

struct hashtab *hashtab_create(int (*hash_value)(struct hashtab *h, const void *key), 
			int (*keycmp)(struct hashtab *h, const void *key1, const void *key2),
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

int key_cmpare(struct hashtab *h, const void *key1, const void *key2, int size)
{
	return strcmp((const char *)key1, (const char *)key2);
}

struct hashtab *hashtab_create(int (*hash_value)(struct hashtab *h, const void *key), 
				int (*keycmp)(struct hashtab *h, const void *key1, const void *key2),
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
	struct hashtab_node *cur, *prev, *new;

	if (!h || h->nel >= HASHTAB_MAX_NODES)
		return -1;

	hvalue = h->hash_value(h, key);
	printf("hvalue:%d\n", hvalue);

	prev = NULL;
	cur = h->htable[hvalue];
	while (cur && h->keycmp(h, key, cur->key)>0 ) {
		prev = cur;
		cur = cur->next;
	}

	if (cur && h->keycmp(h, key, cur->key) == 0) {
		printf("not insert\n");
		return -1;
	}

	new = (struct hashtab_node *)malloc(sizeof(struct hashtab_node));
	if (!new)
		return -1;

	new->key = key;
	new->datum = d;

	if (!prev) { //头节点
		//h->htable[hvalue] = new;
		//new->next = NULL;
		printf("head\n");
	} else { //非头节点
		//new->next = prev->next;
		//prev->next = new;
		printf("not head\n");
	}
	
	h->nel++;

	return 0;
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

	hashtab_destroy(h);

	return 0;
}
