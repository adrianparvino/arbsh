/*
Retrieval trees (trie) offer O(1) lookup time after fully populated. 

andy
android
ant
andrew
androgen

barry
barnacle
barney

             [root]
          /          \
       [a]            [b]
        |              |
       [n]            [a]
        |  \           |
       [d] [t]        [r]
     /  |              |  \
   [y] [r]            [r] [n]
        |  \           |   |  \
       [e] [o]        [y] [a] [e]
        |   | \            |   |
       [w] [i] [g]        [c] [y]
            |   |          |
           [d] [e]        [l]
         /      |          |
       [s]     [n]        [e]

*/



#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

/* alphasize must be sufficient to map all ASCII values to an indice */
size_t alphasize = 128;

typedef struct object {
	int leaf; 
	struct object **children; 
}object;

int trie_isleaf(object *o)
{
        return (o->leaf != 0);
}

int trie_isfreenode(object *o)
{
        size_t i;
        for(i = 0; i < alphasize; i++) 
                if(o->children[i])
                        return 0;
        return 1;
}

int trie_nodel(object *o, char *key, size_t level, size_t len)
{
        size_t index;
        if(!(o))
   		return 0;
        if(level == len)
        {
                if(o->leaf)
                {
                        o->leaf = 0;
                        if( trie_isfreenode(o))
                                return 1; 
                }
		return 0;
        } 

        index = key[level];
        if(trie_nodel(o->children[index], key, level+1, len))
        {
                free(o->children[index]);
                o->children[index] = NULL;
                return (!trie_isleaf(o) && trie_isfreenode(o));
        } 
        return 0;
}

object *trie_init(void)
{
	size_t i = 0; 
	object *o = malloc(sizeof(object)); 
	if (!(o))
		return NULL;
	o->leaf = 0; 
	o->children = malloc(sizeof(object) * alphasize);
	if (!(o->children))
		return NULL;
	for (i = 0; i < alphasize; i++) 
		o->children[i] = NULL; 
	return o;
} 

void trie_insert(object *o, const char *pat)
{
	size_t i; 
	size_t ind; 
	for (i = 0; pat[i]; i++)
	{
		ind = pat[i]; 
		if (!o->children[ind])
			o->children[ind] = trie_init(); 
		o = o->children[ind];
	}
	o->leaf = 1;
} 

int trie_search(object *o, const char *pat)
{
	size_t i;
	size_t ind; 
	for (i = 0; pat[i]; i++)
	{
		ind = pat[i];
		if (!o->children[ind])
			return 0; 
		o = o->children[ind];
	} 
	if ( o != NULL && o->leaf)
		return 1;
	return 0; 
} 

void trie_free(object* root)
{ 
	size_t i;
	for (i = 0; i < alphasize; i++)
	{
		if (root->children[i])
			trie_free(root->children[i]);
	}
	free(root->children);
	free(root);
}

void trie_histogram(object* root, size_t level)
{ 
	size_t i; 
	static char str[100];
	
	static int once = 1;
	if (once)
	{
		printf("root\n|\n|\n|");
		once = 0;
	}

	if (root->leaf)
	{
		str[level] = '\0';
		printf("    -->(%s)\n|", str); 
	} 
    
	for (i = 0; i < alphasize; i++)
	{ 
		if (root->children[i])
		{
			printf("-%c", (int)i);
			str[level] = i; 
			trie_histogram(root->children[i], level + 1);
		}
	}
}

void trie_display(object* root, size_t level)
{ 
	size_t i; 
	static char str[100]; 

	if (root->leaf)
	{
		str[level] = '\0';
		printf("%s\n", str); 
	} 
    
	for (i = 0; i < alphasize; i++)
	{ 
		if (root->children[i])
		{ 
			str[level] = i; 
			trie_display(root->children[i], level + 1);
		}
	}
}

int main(void)
{ 
	size_t i;
	char patterns[][10] = {"The!", "the", "there", "answer", "any", "by", "bye", "th@eir", "123", "~~~", "zzzzz"}; 
	char queries[][10] = {"The!", "thaw", "th@eir", "these", "123", "~~~", "zzzzz", "th"};

	object *root = trie_init(); 

	for (i=0; i < sizeof(patterns)/sizeof(patterns[0]); ++i)
		trie_insert(root, patterns[i]); 
	for (i=0; i < sizeof(queries)/sizeof(queries[0]); ++i)
	{ 
                if (!(trie_search(root, queries[i])))
			printf("%s  -- Not found\n", queries[i]);
		else
			printf("%s  -- Found\n", queries[i]);
	} 
	trie_display(root, 0);
	trie_nodel((root), patterns[1] , 0, strlen(patterns[1]));
	printf("\n\n\n");
	trie_display(root, 0);
	printf("\n\n\n");
	trie_histogram(root, 0);
	trie_free(root);
	return 0;
}
