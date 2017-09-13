//TST.h
#ifndef TST_H
#define TST_H
//#define DEBUG_PROGRAM_MEMORY
 
//Node of a Ternary Search Tree
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
#ifdef DEBUG_PROGRAM_MEMORY
#include <map>
 
static std::map<TSTNode*, char> mem_addrs;
void CheckTSTMem();
#endif
 
#endif
