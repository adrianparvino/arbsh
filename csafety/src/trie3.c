#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


size_t alphasize = 26;
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 
#define INDEX(c) ((size_t)c - (size_t)'a')
#define FREE(p) \
	free(p);	\
	p = NULL;

typedef struct object object;
typedef struct object // trie node
{
	size_t leaf; // non zero if leaf
	object *children[26];
} object; 

typedef struct trie trie_t; // trie ADT
 
struct trie
{
	object *root;
	size_t count;
};
 
object *getNode(void)
{
	object *o = NULL;
	size_t i = 0; 
	o = malloc(sizeof(object)); 
	if( o )
	{ 
		o->leaf = 0; 
		for(i = 0; i < alphasize; i++) 
			o->children[i] = NULL; 
	} 
	return o;
}
 
void initialize(trie_t *pTrie)
{
	pTrie->root = getNode();
	pTrie->count = 0;
}
 
void insert(trie_t *pTrie, char key[])
{
	size_t level;
	size_t length = strlen(key);
	size_t index;
	object *o;
 
	pTrie->count++;
	o = pTrie->root;
 
	for( level = 0; level < length; level++ )
	{
		index = INDEX(key[level]);
 
		if( o->children[index] )
		{ 
			o = o->children[index]; // Skip current node
		}
		else // Add new node
		{ 
			o->children[index] = getNode();
			o = o->children[index];
		}
	} 
	
	o->leaf = pTrie->count; // mark last node as leaf (non zero)
}
 
size_t search(trie_t *pTrie, char key[])
{
	size_t level;
	size_t length = strlen(key);
	size_t index;
	object *o;
 
	o = pTrie->root;
 
	for( level = 0; level < length; level++ )
	{
		index = INDEX(key[level]); 
		if( !o->children[index])
			return 0; 
		o = o->children[index];
	}
 
	return (0 != o && o->leaf);
}
 
size_t leafNode(object *o)
{
	return (o->leaf != 0);
}
 
size_t isItFreeNode(object *o)
{
	size_t i;
	for(i = 0; i < alphasize; i++)
	{
		if( o->children[i] )
			return 0;
	}
 
	return 1;
}
 
bool deleteHelper(object *o, char key[], size_t level, size_t len)
{
	size_t index;
	if( o )
	{
		if( level == len ) // Base case
		{
			if( o->leaf )
			{
				o->leaf = 0; // Unmark leaf node 
				if( isItFreeNode(o) ) 	// If empty, node to be deleted 
					return true; 
				return false;
			}
		}
		else // Recursive case
		{
			index = INDEX(key[level]); 
			if( deleteHelper(o->children[index], key, level+1, len) )
			{ 
				FREE(o->children[index]); 	// last node marked, delete it 
				return ( !leafNode(o) && isItFreeNode(o) ); 	// recursively climb up, and delete eligible nodes
			}
		}
	}
	return false;
} 
 
size_t main()
{
	char keys[][8] = {"she", "sells", "sea", "shore", "the", "by", "sheer"};
	trie_t trie;
	size_t i = 0;
 
	initialize(&trie);
 
	for(i = 0; i < ARRAY_SIZE(keys); i++) 
		insert(&trie, keys[i]); 
 
	//deleteKey(&trie, keys[0]); 
	deleteHelper((trie.root), keys[0], 0, strlen(keys[0]));
	printf("%s %s\n", "she", search(&trie, "she") ? "Present in trie" : "Not present in trie");
 
	return 0;
}
