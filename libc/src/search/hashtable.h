#ifndef HASHTABLE_H_
#define HASHTABLE_H_

/* internal headers */
#include <gstdlib.h>
#include <gstdio.h>
#include <glimits.h>
#include <gstring.h>

/* structures and data types */
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

/* functions */
htable_t *htable_create(size_t); 
int htable_hash(htable_t *, char *); 
kv_pair_t *htable_newpair(char *, char *); 
void htable_set(htable_t *, char *, char *);
char *ht_get(htable_t *, char *);

#endif // HASHTABLE_H_
