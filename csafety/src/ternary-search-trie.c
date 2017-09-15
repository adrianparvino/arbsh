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

tstnode* tst_insert(tstnode* root, char* str); 
void tst_tprint(tstnode* root); 
size_t tst_glength(tstnode *root); 
void tst_delete(tstnode *root); 
bool tst_search(tstnode *root, char* pattern); 
int getword(char *, int, FILE *);

int main(int argc, char **argv)
{ 
	tstnode *root = NULL; 

	char word[100];
        FILE *fp = stdin;
        if ( argc == 2 )
                if (!(fp = fopen(argv[1], "r")))
                        return 1;

        while (getword(word, 100, fp) != EOF)
		root= tst_insert(root, word);

	tst_tprint(root); 
	tst_delete(root);
	return 0;
}
	
tstnode* tst_insert(tstnode* root, char* str)
{
	if(root == NULL)
	{
		if (!(root = (tstnode*)malloc(sizeof(tstnode))))
			return NULL;
		root->data = *str;
		root->eos = false;
		root->left = root->eq = root->right = NULL;
	}

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

static void _tst_tprint(tstnode* root, char* buffer, size_t depth)
{
	if (root)
	{ 
		_tst_tprint(root->left, buffer, depth); 
		buffer[depth] = root->data;
		if (root->eos)
		{
			buffer[depth + 1] = '\0';
			printf("%s\n", buffer);
		} 
		_tst_tprint(root->eq, buffer, depth + 1);
		_tst_tprint(root->right, buffer, depth);
	}
} 

void tst_tprint(tstnode* root)
{
	char buffer[1024];
	_tst_tprint(root, buffer, 0);
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
	return ((x)>(y) ? ((x)>(z) ? (x):(z)) : ( (y)>(z) ? (y):(z) ));
}
	
void tst_delete(tstnode *root)
{
	tstnode *tmp = root;
	if (tmp)
	{
		tst_delete(tmp->left);
		tst_delete(tmp->eq);
		tst_delete(tmp->right);
		free(tmp);
	}
} 
int getword(char *word, int lim, FILE *fp)
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

