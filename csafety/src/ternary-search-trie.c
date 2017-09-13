#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

typedef struct tstnode{
        char data;
        bool eos;
        struct tstnode* left;		/* data less than current node */
        struct tstnode* eq;		/* data eq to current node */
        struct tstnode* right;		/* data greater than current node */
}tstnode; 

tstnode* tst_insert(tstnode* root, char* str); 
void tst_tprsize_t(tstnode* root); 
size_t tst_glength(tstnode *root); 
void tst_delete(tstnode *root); 
bool tst_search(tstnode *root, char* pattern);

#define MAX_LEN 1024 
#define MAX( a, b, c ) ((a)>(b) ? ((a)>(c) ? (a):(c)) : ( (b)>(c) ? (b):(c) )) 
	
tstnode* tst_insert(tstnode* root, char* str)
{
	if(root == NULL)
	{
		if (!(root = (tstnode*)malloc(sizeof(tstnode))))
			return NULL;
		root->data = *str;  // insert first character of string in the root node
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
	
//Helper to prsize_t the strings in TST
static void _tst_tprsize_t(tstnode* root, char* buffer, size_t depth)
{
	if (root)
	{ 
		_tst_tprsize_t(root->left, buffer, depth); 
		buffer[depth] = root->data;
		if (root->eos) //Once end of string flag is encountered, print the string
		{
			buffer[depth + 1] = '\0';
			printf("%s\n", buffer);
		} 
		_tst_tprsize_t(root->eq, buffer, depth + 1);
		_tst_tprsize_t(root->right, buffer, depth);
	}
}
	
// Function to print TST's strings
void tst_tprsize_t(tstnode* root)
{
	char buffer[MAX_LEN];
	_tst_tprsize_t(root, buffer, 0);
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
	
//Function to determine largest 
size_t tst_glength(tstnode *root)
{
	if (root == NULL)
		return 0;
	
	size_t leftLen = tst_glength(root->left);
	size_t middleLen = tst_glength(root->eq) + 1;
	size_t rightLen = tst_glength(root->right);
	
	return MAX( leftLen, middleLen, rightLen);
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
	
int main(int argc, char **argv)
{
	char *str = "hello";
	char *str1 = "bat";
	tstnode *root = NULL;
	root = tst_insert(root, "boats");
	root = tst_insert(root, "boat");
	root = tst_insert(root, "bat");
	root = tst_insert(root, "bats");
	root = tst_insert(root, "stages");

	tst_tprsize_t(root);

	if (tst_search(root, str) == false)
		printf("%s not found\n", str);
	else
		printf("%s found\n", str);

	if (tst_search(root, str1) == false)
		printf("%s not found\n", str1);
	else
		printf("%s found\n", str1);

	tst_delete(root);
	return 0;
}
