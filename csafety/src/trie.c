#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 
#define ALPHABET_SIZE (26) 

typedef struct object
{
	struct object *children[ALPHABET_SIZE]; 
	bool isLeaf; // isLeaf is true if the node represents end of a word
}object;

object *initnode(void)
{
	size_t i = 0; 
	object *o = malloc(sizeof(object)); 
	if (o)
	{ 
		o->isLeaf = false; 
		for (i = 0; i < ALPHABET_SIZE; i++)
			o->children[i] = NULL;
	} 
	return o;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(object *root, const char *key)
{
	size_t level;
	size_t len = strlen(key);
	size_t index; 
	object *o = root;
	for (level = 0; level < len; level++)
	{
		// use only 'a' through 'z' and lower case
		index = key[level] - 'a';
		if (!o->children[index])
			o->children[index] = initnode(); 
		o = o->children[index];
	}
	o->isLeaf = true; // mark last node as leaf
}

// Returns true if key presents in trie, else false
bool search(object *root, const char *key)
{
	size_t level;
	size_t len = strlen(key);
	size_t index;
	object *o = root; 
	for (level = 0; level < len; level++)
	{ 
		index = key[level] - 'a';
		if (!o->children[index])
			return false; 
		o = o->children[index];
	} 
	return (o != NULL && o->isLeaf);
}

int main(void)
{
	// Input keys (use only 'a' through 'z' and lower case)
	size_t i;
	char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"}; 
	char output[][32] = {"Not present in trie", "Present in trie"}; 
	object *root = initnode(); 
	
	for (i = 0; i < ARRAY_SIZE(keys); i++)
		insert(root, keys[i]);

	// Search for different keys
	printf("%s --- %s\n", "the", output[search(root, "the")] );
	printf("%s --- %s\n", "these", output[search(root, "these")] );
	printf("%s --- %s\n", "their", output[search(root, "their")] );
	printf("%s --- %s\n", "thaw", output[search(root, "thaw")] );

	return 0;
}
