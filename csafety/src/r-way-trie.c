/*
Retrieval trees (tries) offer 0(N) search and insertion time. Tries have the
unique property of aborting upon an "early miss", which greatly increases their
effectiveness.  

	"Proposition G. The number of array accesses when 
	 searching in a trie or inserting a key into a trie
	 is at most 1 plus the length of the key." 
		 (Sedgewick, "Algorithms" 4th ed. pg730)


Typically in depictions of tries NULL nodes are not shown, as is the case in
the depiction below:


	    [root]           andy
	  /	  \          android
       [a]        [b]	     ant
	|          |         andrew
       [n]        [a]	     androgen
	|  \	   |
       [d] [t]    [r]	     barry
     /  |          |  \	     barnacle
   [y] [r]        [r] [n]    barney
	|  \	   |   |  \
       [e] [o]    [y] [a] [e]
	|   | \        |   |
       [w] [i] [g]    [c] [y]
	    |   |      |
	   [d] [e]    [l]
	 /      |      |
       [s]     [n]    [e]
	
	
The program below presents an R-way trie. Insertion, deletion, searching,
printing and histogram functions are supplied.
	
	
*/ 
	
	#include <stdio.h>
	#include <stdlib.h> 
	#include <string.h>
	
	/* map all ASCII values to an indice */
	size_t alphasize = 128;
	
	typedef struct object {
		int leaf; 
		struct object **children; 
	}object;
	
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
			return 0;
		} 
	
		index = key[level];
		if(_trie_nodel(o->children[index], key, level+1))
		{
			free(o->children[index]);
			o->children[index] = NULL; /* FIXME !!  _trie_nodel should return an object * */
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
	
	int main(void)
	{ 
		size_t i;
		char patterns[][10] = {"The!", "the", "there", "answer",
		 "any", "by", "bye", "th@eir", "123", "~~~", "zzzzz"}; 
		char queries[][10] = {"The!", "thaw", "th@eir", "these",
		 "123", "~~~", "zzzzz", "th"};
	
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
		
		trie_display(root);
		trie_nodel((root), patterns[1]);
		printf("\n");
		trie_display(root);
		printf("\n");
		trie_histogram(root);
		trie_free(root);
		return 0;
	}
