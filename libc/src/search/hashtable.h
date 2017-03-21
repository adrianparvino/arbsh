#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

struct kv_pair{
	char *key;
	char *value;
	struct kv_pair *next;
};
typedef struct kv_pair kv_pair_t;

struct htable{
	int size;
	struct kv_pair_t **table;
};
typedef struct htable htable_t;

htable_t *htable_create(int size);

int htable_hash(htable_t *htable_v, char *key);

kv_pair_t *htable_newpair(char *key, char *value);

void htable_set(htable_t *htable_v, char *key, char *value);
char *ht_get(htable_t *htable_v, char *key);

#endif // HASHTABLE_H_