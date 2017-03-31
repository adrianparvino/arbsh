#include "hashtable.h"

htable_t *htable_create(int size){
	int i = 0;
	htable_t *htable_v = NULL;
	if(size <= 0)
		return NULL;
	if((htable_v = malloc(sizeof(htable_t)))== NULL)
		return NULL;
	if( ( htable_v->table = malloc( sizeof( kv_pair_t * ) * size ) ) == NULL ) 
		return NULL;
	for(i = 0; i < size; i++){
		htable_v->table[i] = NULL;
	}
	htable_v->size = size;
	return htable_v;
}


int htable_hash(htable_t *htable_v, char *key){
	unsigned long int hval;
	size_t i = 0;
	size_t len = strlen(key);
	while(hval < ULONG_MAX && i < len){
		hval = hval << 8;
		hval += key[i];
		i++;
	}
	return hval % htable_v->size;
}

kv_pair_t *htable_newpair(char *key, char *value){
	kv_pair_t *newpair = NULL;
	if((newpair = malloc(sizeof(kv_pair_t)))==NULL)
		return NULL;
	if((newpair->key = strdup(key))==NULL)
		return NULL;
	if((newpair->value = strdup(value))==NULL)
		return NULL;
	newpair->next = NULL;
	return newpair;
}

void htable_set(htable_t *htable_v,char *key,char *value){
	value = value;
	key = key;
	htable_v = htable_v;
	//TODO: finish up the htable_set method that actually allows us to populate the damn thing
}
char *htable_get(htable_t *htable_v,char *key){
	htable_v = htable_v;
	//int bin = 0;
	kv_pair_t *pair;

	//bin = htable_hash(htable_v,key);

	//pair = htable_v->table[bin];
	while(pair != NULL && pair->key != NULL && strcmp(key,pair->key) > 0){
		pair = pair->next;
	}
	if(pair == NULL || pair->key == NULL || strcmp(key,pair->key) != 0)
		return NULL;
	else
		return pair->value;
}

