//Main.cpp
#include <iostream>

#include <cstdlib>
#include <utility>
//#include "TST.h"
typedef struct TSTNode{
        char data; //Actual data stored in form of character
        bool bEOS; //flag marking end of string
        struct TSTNode* left;   //All character data less than this node
        struct TSTNode* eq;  //All character data equal to this node
        struct TSTNode* right; //All character data greater than this node
}TSTNode;

//Inserts a string in the TST
TSTNode* Insert(TSTNode* root, char* str);

//Prints all strings in the TST
void PrintAllStringsInTST(TSTNode* root);

//Gets the length of maximum length string in TST
int MaxLenStringLen(TSTNode *root);

//Deleted the complete TST
void DeleteTST(TSTNode *root);

//Search a pattern in TST
bool SearchTST(TSTNode *root, char* pattern);

//Prints 
//#ifdef DEBUG_PROGRAM_MEMORY
#include <map>

static std::map<TSTNode*, char> mem_addrs;
void CheckTSTMem();

////TST.cpp
//#include <iostream>
#define DEBUG_PROGRAM_MEMORY
//	
//#include "TST.h"
	
#define MAX_LEN 1024
	
#define MAX( a, b, c ) ((a)>(b) ? ((a)>(c) ? (a):(c)) : ( (b)>(c) ? (b):(c) ))
	
	
TSTNode* Insert(TSTNode* root, char* str)
{
	if(root == NULL)
	{
		root = (TSTNode*)malloc(sizeof(TSTNode));
		if(root == NULL)
		{
			std::cout<<"Memory allocation failed"<<std::endl;
			return NULL;
		}
	
		//Insert first character of string in the root node
		root->data = *str;
#ifdef DEBUG_PROGRAM_MEMORY
		mem_addrs.insert(std::make_pair(root, root->data));
#endif
		root->bEOS = false;
		root->left = root->eq = root->right = NULL;
	}
		
	if(*str  < root->data)
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
static void PrintHelper(TSTNode* root, char* buffer, int depth)
{
	if (root)
	{
		// Traverse the left subtree
		PrintHelper(root->left, buffer, depth);
	
		buffer[depth] = root->data;
		//Once end of string flag is encountered, print the string
		if (root->bEOS)
		{
			buffer[depth + 1] = '\0';
			std::cout<< buffer << std::endl;
		}
	
		// Traverse the middle subtree
		PrintHelper(root->eq, buffer, depth + 1);
	
		// Traverse the right subtree
		PrintHelper(root->right, buffer, depth);
	}
}
	
// Function to print TST's strings
void PrintAllStringsInTST(TSTNode* root)
{
	char buffer[MAX_LEN];
	PrintHelper(root, buffer, 0);
}
	
bool SearchTST(TSTNode *root, char* pattern)
{
	while (root != NULL)
	{
		if (*pattern < root->data)
			root = root->left;
		else if (*pattern == root->data)
		{
			//If end of string flag is found and the pattern length is also exhausted, 
			//we can safely say that the pattern is present in the TST
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
int MaxLenStringLen(TSTNode *root)
{
	if (root == NULL)
		return 0;
	
	int leftLen = MaxLenStringLen(root->left);
	int middleLen = MaxLenStringLen(root->eq) + 1;
	int rightLen = MaxLenStringLen(root->right);
	
	return MAX( leftLen, middleLen, rightLen);
}
	
void DeleteTST(TSTNode *root)
{
	TSTNode *tmp = root;
	if (tmp)
	{
		DeleteTST(tmp->left);
		DeleteTST(tmp->eq);
		DeleteTST(tmp->right);
	
#ifdef DEBUG_PROGRAM_MEMORY
		mem_addrs.erase(tmp);
#endif
		delete tmp;
	}
}
	
#ifdef DEBUG_PROGRAM_MEMORY
void CheckTSTMem()
{
	std::map<TSTNode*, char>::iterator itr = mem_addrs.begin();
	
	if (mem_addrs.size() == 0)
	{
		std::cout << "No memory leaks";
		return;
	}
	
	while (itr != mem_addrs.end()) 
	{
		std::cout << "Memory address " << itr->first<< " for \"" << itr->second << "\" has not been deallocated" << std::endl;
		++itr;
	}
}
#endif



	
int main(int argc, char** argv) {
		
	TSTNode *root = NULL;
	root = Insert(root, "boats");
	root = Insert(root, "boat");
	root = Insert(root, "bat");
	root = Insert(root, "bats");
	root = Insert(root, "stages");
	
	PrintAllStringsInTST(root);
	std::cout << "Maximum length string in this TST is of size "<< MaxLenStringLen(root) << std::endl;
	
	char *str = "hello";
	char *str1 = "bat";
	
	if (SearchTST(root, str) == false)
		std::cout << "\""<<str<<"\" not found in TST" << std::endl;
	else
		std::cout << "\"" << str << "\" is present in TST" << std::endl;
	
	if (SearchTST(root, str1) == false)
		std::cout << "\"" << str << "\" not found in TST" << std::endl;
	else
		std::cout << "\"" << str1 << "\" is present in TST" << std::endl;
	
	DeleteTST(root);
	
#ifdef DEBUG_PROGRAM_MEMORY
	CheckTSTMem();
#endif
		
	return 0;
}
