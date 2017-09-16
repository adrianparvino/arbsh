/*
Retrieval trees (tries) offer 0(N) search and insertion time. Tries have the
unique property of aborting upon an "early miss", which greatly increases their
effectiveness.  

"Proposition G. The number of array accesses when 
 searching in a trie or inserting a key into a trie
 is at most 1 plus the length of the key." 
	 (Sedgewick, "Algorithms" 4th ed. pg730)


The program below presents an R-way trie. Insertion, deletion, searching,
printing and histogram functions are supplied.


*/ 

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

/* map all ASCII values to an indice */
size_t alphasize = 128;

typedef struct object {
	int leaf; 
	struct object **children; 
	//struct object *children[128];
}object;

int trie_childfree(object *o)
{
	size_t i;
	for(i = 0; i < alphasize; i++)
		if(o->children[i])
			free(o->children[i]);
	return 1;
}
int trie_isfreenode(object *o)
{
	size_t i;
	for(i = 0; i < alphasize; i++)
		if(o->children[i])
			return 0;
	return 1;
}

int _trie_nodel(object *o, char *key, size_t level)
{ 
	size_t index;
	if(!(o))
   		return 0;
	if(key[level] == 0)
	{
		if(o->leaf)
		{
			o->leaf = 0;
			if(trie_isfreenode(o))
				return 1; 
		
		}
		//trie_childfree(o->children[index]);
		return 0 ;
		
	} 
	index = key[level];
	if(_trie_nodel(o->children[index], key, level+1))
	{
		//if(o->leaf)
		//	o->leaf = 0;
		//trie_childfree(o->children[index]);
		//if (o->children[index]->children)
		free(o->children[index]->children);
		free(o->children[index]);
	
		o->children[index] = NULL; 
		//_trie_nodel(o, key, level+1);
		//free(o->children);
		
		//return 1;
		return (!o->leaf && trie_isfreenode(o));
	}
	return 0;
}

int trie_nodel(object *o, char *key)
{
	size_t level = 0;
	_trie_nodel(o, key, level);
}

object *trie_init(void)
{
	size_t i = 0; 
	object *o = malloc(sizeof(object)); 
	if (!(o))
		return NULL;
	o->leaf = 0;
	if (!(o->children = malloc(sizeof(object) * alphasize)))
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
int trie_newdel(object *o, const char *pat)
{
        size_t i;
	size_t j = 0;
        size_t ind;
	object *p[1024];
        for (i = 0; pat[i]; i++)
        {
                ind = pat[i];
                if (!o->children[ind])
			break;
                  //      return;
		if(!trie_isfreenode(o))
			o->leaf = 1;
		p[j++] = o;
		//object *tmp = o;
                o = o->children[ind];
		

		
		//	free(tmp);
        }
     	//for(i=0; i<j; ++i)
	for (;j--;)
	{
		if (p[j]->leaf == 1)
		free(p[j]);
		
		//if(!trie_isfreenode(p[j]))
		//	p[j]->leaf = 0;
		
		//p[j] = NULL;
	}
      
       
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

void _trie_histogram(object* root, size_t level)
{ 
	size_t i; 
	static char str[100]; 

	if (root->leaf)
	{
		str[level] = '\0';
		printf("\t\t\t    -->(%s)\n|", str); 
	} 
 
	for (i = 0; i < alphasize; i++)
	{ 
		if (root->children[i])
		{
			printf("-%c", (int)i);
			str[level] = i; 
			_trie_histogram(root->children[i], level + 1);
		}
	}
}

void trie_histogram(object* root)
{
	printf("root\n|\n|\n|");
	_trie_histogram(root, 0);
}

void _trie_display(object* root, size_t level)
{ 
	size_t i; 
	static char str[1024];

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
			_trie_display(root->children[i], level + 1); 
		}
	}
}

void trie_display(object* root)
{
	size_t level = 0;
	_trie_display(root, level);
}

int getword(char *word, size_t lim, FILE *fp)
{
        int c;
        char *w = word;
        while (isspace(c = fgetc(fp)));
	        if (c != EOF)
                *w++ = c;
        if (!isalnum(c) && !ispunct(c))
                { *w = '\0'; return c; }
        for ( ; --lim > 0; w++)
        {
                *w = fgetc(fp);
                if (!isalnum(*w) && !ispunct(*w))
                        { ungetc(*w, fp); break; }
        }
        *w = '\0';
        return word[0];
}

int main(int argc, char *argv[])
{ 
	size_t i = 0;
	char word[100];
        FILE *fp = stdin;
        if ( argc == 2 )
                if (!(fp = fopen(argv[1], "r")))
                        return 1;

	object *root = trie_init(); 
	while (getword(word, 100, fp) != EOF)
		trie_insert(root, word);

        if (fp!=stdin)rewind(fp);

        while (getword(word, 100, fp) != EOF)
        {
                if (trie_search(root, word))
                        printf("found %s\n", word);
                else
                        printf("not found %s\n", word);

        }
	trie_display(root);

	if (fp!=stdin)rewind(fp);
	while (getword(word, 100, fp) != EOF) 
			trie_nodel(root, word);
	
		

	if (fp!=stdin)rewind(fp);
	//while (getword(word, 100, fp) != EOF)
	//	trie_insert(root, word);
	trie_display(root);
	//trie_nodel((root), patterns[1]);
	printf("\n");
	trie_display(root);
	printf("\n");
	trie_histogram(root);
	trie_free(root);
	
	return 0;
}

