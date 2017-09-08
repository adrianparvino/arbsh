#include <stdio.h>
#include <stdlib.h>

int asciioff(int a)
{ 
	static int b[300] = { 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 000, 000, 000, 000, 000, 000, 
	000, 000, 001, 002, 003, 004, 005, 006, 
	007, 010, 011, 012, 013, 014, 015, 016, 
	017, 020, 021, 022, 023, 024, 025, 026, 
	027, 030, 031, 032, 033, 034, 035, 036, 
	037, 040, 041, 042, 043, 044, 045, 046, 
	047, 050, 051, 052, 053, 054, 055, 056, 
	057, 060, 061, 062, 063, 064, 065, 066, 
	067, 070, 071, 072, 073, 074, 075, 076, 
	077, 100, 101, 102, 103, 104, 105, 106, 
	107, 110, 111, 112, 113, 114, 115, 116, 
	117, 120, 121, 122, 123, 124, 125, 126, 
	127, 130, 131, 132, 133, 134, 135, 136, 
	137, 140, 141, 142, 143, 144, 145, 146, 
	147, 150, 151, 152, 153, 154, 155, 156, 
	157, 160, 161, 162, 163, 164, 165, 166, 
	167, 170, 171, 172, 173, 174, 175, 176, 
	177, 200, 201 }; 

	return b[a];
}

size_t alphasize = 64;

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
		ind = asciioff(pat[i]);
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
		ind = asciioff(pat[i]);
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
	char  patterns[][10] = {"The!", "a", "there", "answer", "any", "by", "bye", "th@eir", "123"}; 
	char queries[][10] = {"The!", "thaw", "th@eir", "these", "123"};

	object *root = initnode(); 

	for (i=0; i < sizeof(patterns)/sizeof(patterns[0]); ++i)
		insert(root, patterns[i]); 
	for (i=0; i < sizeof(queries)/sizeof(queries[0]); ++i)
	{ 
                if (!( search(root, queries[i])))
			printf("%s  -- Not found\n", queries[i]);
		else
			printf("%s  -- Found\n", queries[i]);
	} 

	return 0;
}
