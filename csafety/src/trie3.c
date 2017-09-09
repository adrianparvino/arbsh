#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
 
// Alphabet size (# of symbols)
 
int alphasize = 26;
#define INDEX(c) ((int)c - (int)'a')
 
#define FREE(p) \
	free(p);	\
	p = NULL;
 
// forward declration
typedef struct object object;
 
// trie node
typedef struct object
{
	int leaf; // non zero if leaf
	object *children[26];
} object;
 
// trie ADT
typedef struct trie trie_t;
 
struct trie
{
	object *root;
	int count;
};
 
object *getNode(void)
{
	object *o = NULL;
 
	o = malloc(sizeof(object));
 
	if( o )
	{
		int i;
 
		o->leaf   = 0;
 
		for(i = 0; i < alphasize; i++)
		{
			o->children[i] = NULL;
		}
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
	int level;
	int length = strlen(key);
	int index;
	object *pCrawl;
 
	pTrie->count++;
	pCrawl = pTrie->root;
 
	for( level = 0; level < length; level++ )
	{
		index = INDEX(key[level]);
 
		if( pCrawl->children[index] )
		{
			// Skip current node
			pCrawl = pCrawl->children[index];
		}
		else
		{
			// Add new node
			pCrawl->children[index] = getNode();
			pCrawl = pCrawl->children[index];
		}
	}
 
	// mark last node as leaf (non zero)
	pCrawl->leaf = pTrie->count;
}
 
int search(trie_t *pTrie, char key[])
{
	int level;
	int length = strlen(key);
	int index;
	object *pCrawl;
 
	pCrawl = pTrie->root;
 
	for( level = 0; level < length; level++ )
	{
		index = INDEX(key[level]);
 
		if( !pCrawl->children[index] )
		{
			return 0;
		}
 
		pCrawl = pCrawl->children[index];
	}
 
	return (0 != pCrawl && pCrawl->leaf);
}
 
int leafNode(object *o)
{
	return (o->leaf != 0);
}
 
int isItFreeNode(object *o)
{
	int i;
	for(i = 0; i < alphasize; i++)
	{
		if( o->children[i] )
			return 0;
	}
 
	return 1;
}
 
bool deleteHelper(object *o, char key[], int level, int len)
{
	if( o )
	{
		// Base case
		if( level == len )
		{
			if( o->leaf )
			{
				// Unmark leaf node
				o->leaf = 0;
 
				// If empty, node to be deleted
				if( isItFreeNode(o) )
				{
					return true;
				}
 
				return false;
			}
		}
		else // Recursive case
		{
			int index = INDEX(key[level]);
 
			if( deleteHelper(o->children[index], key, level+1, len) )
			{
				// last node marked, delete it
				FREE(o->children[index]);
 
				// recursively climb up, and delete eligible nodes
				return ( !leafNode(o) && isItFreeNode(o) );
			}
		}
	}
 
	return false;
}
 
void deleteKey(trie_t *pTrie, char key[])
{
	int len = strlen(key);
 
	if( len > 0 )
	{
		deleteHelper(pTrie->root, key, 0, len);
	}
}
 
int main()
{
	char keys[][8] = {"she", "sells", "sea", "shore", "the", "by", "sheer"};
	trie_t trie;
 
	initialize(&trie);
 
	for(int i = 0; i < ARRAY_SIZE(keys); i++)
	{
		insert(&trie, keys[i]);
	}
 
	deleteKey(&trie, keys[0]);
 
	printf("%s %s\n", "she", search(&trie, "she") ? "Present in trie" : "Not present in trie");
 
	return 0;
}
