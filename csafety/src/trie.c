#include <stdio.h>
#include <stdlib.h>

int arba_idioma(int a, int s)
{
	static int ascii[200] = { 
	'0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '!', '"', '#', '$', '%', '&', '\'', 
	'(', ')', '*', '+', ',', '-', '.', '/', 
	'0', '1', '2', '3', '4', '5', '6', '7', 
	'8', '9', ':', ';', '<', '=', '>', '?', 
	'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 
	'X', 'Y', 'Z', '[', '\\', ']', '^', '_', 
	'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 
	'x', 'y', 'z', '{', '|', '}', '~' }; 

	static int iisca[300]  = { 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 
	3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 
	13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 
	23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 
	33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 
	43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 
	53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 
	63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 
	73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 
	83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 
	93, 94, 95, 96, 97, 98, 99, 100, 101, 
	102, 103, 104, 105, 106, 107, 108, 109, 
	110, 111, 112, 113, 114, 115, 116, 117, 
	118, 119, 120, 121, 122, 123, 124, 125, 
	126, 127, 128, 129 }; 

        static int glyphs[65] = { 
	'0', '1', '2', '3', '4', '5', '6', '7', '8',
        '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
        'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
        'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '+',
        '/', '='};
        if (s == 0)
	        return iisca[a];
	
        if (s == 1)
	        return ascii[a];
	
        if (s == 2)
	        return glyphs[a]; 
        
	return a;
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
		//ind = pat[i] - 'a';
		ind = arba_idioma(pat[i], 0);
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
		//ind = pat[i] - 'a';
		ind = arba_idioma(pat[i], 0);
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
	char patterns[][10] = {"The!", "a", "there", "answer", "any", "by", "bye", "th@eir"}; 
	char queries[][10] = {"The!", "thaw", "th@eir", "these"};

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
