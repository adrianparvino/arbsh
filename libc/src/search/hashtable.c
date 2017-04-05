#include "hashtable.h"

htable_t *htable_create(size_t size)
{
	size_t i = 0;
	htable_t *htable_v = NULL;
	if(size <= 0)
		return NULL;
	if((htable_v = gmalloc(sizeof(htable_t))) == NULL)
		return NULL;
	if((htable_v->table = gmalloc(sizeof(kv_pair_t *) * size)) == NULL) 
		return NULL;
	for(i = 0; i < size; i++){
		htable_v->table[i] = NULL;
	}
	htable_v->size = size;
	return htable_v;
}

int htable_hash(htable_t *htable_v, char *key)
{ 
	size_t hval = 0; // TODO: add ULONG_MAX to glimits.h, use size_t for now
	size_t i = 0;
	size_t len = gstrlen(key);

	for(i = 0; hval < GSIZE_MAX && i < len; ++i)
	{
		hval = hval << 8;
		hval += key[i];
	}
	return hval % htable_v->size;
}

kv_pair_t *htable_newpair(char *key, char *value)
{
	kv_pair_t *newpair = NULL;
	if((newpair = gmalloc(sizeof(kv_pair_t)))==NULL)
		return NULL;
	if((newpair->key = gstrdup(key))==NULL)
		return NULL;
	if((newpair->value = gstrdup(value))==NULL)
		return NULL;
	newpair->next = NULL;
	return newpair;
}

void htable_set(htable_t *htable_v,char *key,char *value)
{
	value = value;				// suppress warnings
	key = key;
	htable_v = htable_v;
	//TODO: finish up the htable_set method that actually allows us to populate the damn thing
}

char *htable_get(htable_t *htable_v,char *key)
{
	htable_v = htable_v; 			// suppress warnings
	//int bin = 0; 				// suppress warnings
	kv_pair_t *pair;

	//bin = htable_hash(htable_v,key);	// suppress warnings

	//pair = htable_v->table[bin];		// suppress warnings
	while(pair != NULL && pair->key != NULL && gstrcmp(key,pair->key) > 0){
		pair = pair->next;
	}
	if(pair == NULL || pair->key == NULL || gstrcmp(key,pair->key) != 0)
		return NULL;
	else
		return pair->value;
}

