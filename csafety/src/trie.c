#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 
#define ALPHABET_SIZE (26) 

typedef struct object
{
	struct object **children; 
	bool leaf;
}object;

object *initnode(void)
{
	size_t i = 0; 
	object *o = malloc(sizeof(object)); 
	if (!(o))
		return NULL;
	o->leaf = false;
	o->children = malloc(sizeof(object*) * ALPHABET_SIZE);
	if (!(o->children))
		return NULL;
	for (i = 0; i < ALPHABET_SIZE; i++) 
		o->children[i] = NULL; 
	return o;
} 

void insert(object *root, const char *key)
{
	size_t level; 
	size_t index; 
	object *o = root;
	for (level = 0; key[level]; level++)
	{ 
		index = key[level] - 'a';
		if (!o->children[index])
			o->children[index] = initnode(); 
		o = o->children[index];
	}
	o->leaf = true;
} 

bool search(object *root, const char *key)
{
	size_t level;
	size_t index;
	object *o = root; 
	for (level = 0; key[level]; level++)
	{ 
		index = key[level] - 'a';
		if (!o->children[index])
			return false; 
		o = o->children[index];
	} 
	return (o != NULL && o->leaf);
}

int main(void)
{ 
	size_t i;
	char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"}; 
	char output[][32] = {"Not present in trie", "Present in trie"}; 
	object *root = initnode(); 
	
	for (i = 0; i < ARRAY_SIZE(keys); i++)
		insert(root, keys[i]); 

	printf("%s --- %s\n", "the", output[search(root, "the")] );
	printf("%s --- %s\n", "these", output[search(root, "these")] );
	printf("%s --- %s\n", "their", output[search(root, "their")] );
	printf("%s --- %s\n", "thaw", output[search(root, "thaw")] );

	return 0;
}
