#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

typedef struct tstnode{
        char data;
        bool bEOS;
        struct tstnode* left;   //All character data less than this node
        struct tstnode* eq;  //All character data equal to this node
        struct tstnode* right; //All character data greater than this node
}tstnode; 

tstnode* Insert(tstnode* root, char* str); 
void PrintAllStringsInTST(tstnode* root); 
int MaxLenStringLen(tstnode *root); 
void DeleteTST(tstnode *root); 
bool SearchTST(tstnode *root, char* pattern);

#define MAX_LEN 1024 
#define MAX( a, b, c ) ((a)>(b) ? ((a)>(c) ? (a):(c)) : ( (b)>(c) ? (b):(c) )) 
	
tstnode* Insert(tstnode* root, char* str)
{
	if(root == NULL)
	{
		if (!(root = (tstnode*)malloc(sizeof(tstnode))))
			return NULL;
		root->data = *str;  //Insert first character of string in the root node
		root->bEOS = false;
		root->left = root->eq = root->right = NULL;
	}

	if(*str < root->data)
		root->left = Insert(root->left, str);
	else if (*str == root->data)
	{
		if(*(str + 1))
			root->eq = Insert(root->eq, str + 1);
		else
			root->bEOS = true;
	}
	else
		root->right = Insert(root->right, str);

	return root; 
}
	
//Helper to print the strings in TST
static void PrintHelper(tstnode* root, char* buffer, int depth)
{
	if (root)
	{ 
		PrintHelper(root->left, buffer, depth); 
		buffer[depth] = root->data;
		if (root->bEOS) //Once end of string flag is encountered, print the string
		{
			buffer[depth + 1] = '\0';
			printf("%s\n", buffer);
		} 
		PrintHelper(root->eq, buffer, depth + 1);
		PrintHelper(root->right, buffer, depth);
	}
}
	
// Function to print TST's strings
void PrintAllStringsInTST(tstnode* root)
{
	char buffer[MAX_LEN];
	PrintHelper(root, buffer, 0);
}
	
bool SearchTST(tstnode *root, char* pattern)
{
	while (root != NULL)
	{
		if (*pattern < root->data)
			root = root->left;
		else if (*pattern == root->data)
		{
			if (root->bEOS && *(pattern + 1) == '\0')
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
int MaxLenStringLen(tstnode *root)
{
	if (root == NULL)
		return 0;
	
	int leftLen = MaxLenStringLen(root->left);
	int middleLen = MaxLenStringLen(root->eq) + 1;
	int rightLen = MaxLenStringLen(root->right);
	
	return MAX( leftLen, middleLen, rightLen);
}
	
void DeleteTST(tstnode *root)
{
	tstnode *tmp = root;
	if (tmp)
	{
		DeleteTST(tmp->left);
		DeleteTST(tmp->eq);
		DeleteTST(tmp->right);
		free(tmp);
	}
} 
	
int main(int argc, char** argv)
{
	char *str = "hello";
	char *str1 = "bat";
	tstnode *root = NULL;
	root = Insert(root, "boats");
	root = Insert(root, "boat");
	root = Insert(root, "bat");
	root = Insert(root, "bats");
	root = Insert(root, "stages");

	PrintAllStringsInTST(root);

	if (SearchTST(root, str) == false)
		printf("%s not found\n", str);
	else
		printf("%s found\n", str);

	if (SearchTST(root, str1) == false)
		printf("%s not found\n", str1);
	else
		printf("%s found\n", str1);

	DeleteTST(root);
	return 0;
}
