#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct tstnode {
	char data;
	bool eos;
	struct tstnode* left;
	struct tstnode* eq;
	struct tstnode* right;
}tstnode; 

tstnode *tst_insert(tstnode *, char *);
void tst_tprint(tstnode *);
void _tst_tprint(tstnode *, char *, size_t, size_t);
size_t tst_glength(tstnode *);
void tst_destroy(tstnode *);
bool tst_search(tstnode *, char *);
int getword(char *, size_t, FILE *);
tstnode *_tst_initnode(int);

int main(int argc, char **argv)
{ 
	tstnode *root = NULL; 

	char word[100];
	FILE *fp = stdin;
	if ( argc == 2 )
		if (!(fp = fopen(argv[1], "r")))
			return 1;

	while (getword(word, 100, fp) != EOF)
		root = tst_insert(root, word);
	
	if (fp!=stdin)rewind(fp);

	while (getword(word, 100, fp) != EOF)
	{
		if (tst_search(root, word))
			printf("found %s\n", word);
		else
			printf("not found %s\n", word); 
	}
	tst_tprint(root);
	if (fp!=stdin)rewind(fp);
	printf("====\n");
	tst_tprint(root); 
	tst_destroy(root);
	if (fp!=stdin)fclose(fp);
	return 0;
}

tstnode *_tst_initnode(int s)
{
	tstnode *root;
	if (!(root = malloc(sizeof(tstnode))))
		return NULL;
	root->data = s;
	root->eos = false;
	root->left = root->eq = root->right = NULL;
	return root;
}
	
tstnode* tst_insert(tstnode* root, char* str)
{ 
	if(!(root))
		if(!((root = _tst_initnode(*str))))
			return NULL;

	if(*str < root->data)
		root->left = tst_insert(root->left, str);
	else if (*str == root->data)
	{
		if(*(str + 1))
			root->eq = tst_insert(root->eq, str + 1);
		else
			root->eos = true;
	}
	else
		root->right = tst_insert(root->right, str);

	return root; 
}

void _tst_tprint(tstnode* root, char* buffer, size_t depth, size_t lim)
{
	if (lim == depth)
		{ fprintf(stderr, "Buffer exhausted\n"); return; }

	if (root)
	{ 
		_tst_tprint(root->left, buffer, depth, lim); 
		buffer[depth] = root->data;
		if (root->eos)
		{
			buffer[depth + 1] = '\0';
			printf("(%s)\n", buffer);
		} 
		_tst_tprint(root->eq, buffer, depth + 1, lim);
		_tst_tprint(root->right, buffer, depth, lim);
	}
} 

void tst_tprint(tstnode* root)
{
	char buffer[1024];
	_tst_tprint(root, buffer, 0, 1024);
} 

bool tst_search(tstnode *root, char* pattern)
{
	while (root != NULL)
	{
		if (*pattern < root->data)
			root = root->left;
		else if (*pattern == root->data)
		{
			if (root->eos && *(pattern + 1) == '\0')
				return true;
			pattern++;
			root = root->eq;
		}
		else
			root = root->right;
	}
	return false;
}

size_t tst_glength(tstnode *root)
{
	size_t x, y, z;

	if (root == NULL)
		return 0;

	x = tst_glength(root->left);
	y = tst_glength(root->eq) + 1;
	z = tst_glength(root->right); 
	return ((x)>(y)?((x)>(z)?(x):(z)):((y)>(z)?(y):(z)));
}
	
void tst_destroy(tstnode *root)
{
	tstnode *tmp = root;
	if (tmp)
	{
		tst_destroy(tmp->left);
		tst_destroy(tmp->eq);
		tst_destroy(tmp->right);
		free(tmp);
	}
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
