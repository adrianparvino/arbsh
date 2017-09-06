#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 
size_t alphasize = 26;

typedef struct object {
	int leaf;
	struct object **children; 
}object;

object *initnode(void)
{
	size_t i = 0; 
	object *o = malloc(sizeof(object)); 
	if (!(o))
		return NULL;
	o->leaf = 0;
	o->children = malloc(sizeof(object*) * alphasize);
	if (!(o->children))
		return NULL;
	for (i = 0; i < alphasize; i++) 
		o->children[i] = NULL; 
	return o;
} 

void insert(object *o, const char *pat)
{
	size_t i; 
	size_t ind; 
	for (i = 0; pat[i]; i++)
	{ 
		ind = pat[i] - 'a';
		if (!o->children[ind])
			o->children[ind] = initnode(); 
		o = o->children[ind];
	}
	o->leaf = 1;
} 

int search(object *o, const char *pat)
{
	size_t i;
	size_t ind; 
	for (i = 0; pat[i]; i++)
	{ 
		ind = pat[i] - 'a';
		if (!o->children[ind])
			return 0; 
		o = o->children[ind];
	} 
	if ( o != NULL && o->leaf)
		return 1;
	return 0; 
}

int main(void)
{ 
	size_t i;
	char patterns[][10] = {"the", "a", "there", "answer", "any", "by", "bye", "their"}; 
	char queries[][10] = {"the", "thaw", "their", "these"};

	object *root = initnode(); 

	for (i=0; i < sizeof(patterns)/sizeof(patterns[0]); ++i)
		insert(root, patterns[i]); 
	for (i=0; i < sizeof(queries)/sizeof(queries[0]); ++i)
	{ 
                if (!( search(root, queries[i])))
			printf("%s --  Not found\n", queries[i]);
		else
			printf("%s --  Found\n", queries[i]);
	} 
	return 0;
}
