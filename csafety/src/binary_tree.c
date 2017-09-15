/*

	REFERENCES:
		K&R2
		http://cslibrary.stanford.edu/110/BinaryTrees.pdf
		http://cslibrary.stanford.edu/109/TreeListRecursion.pdf
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* structures */
typedef struct tnode { 
	char *word;
	int count;
	size_t depth;
	struct tnode *small;
	struct tnode *large;
}tnode;
 
/* prototypes */ 
int ngetch(FILE *); 
int getch(void);
void ungetch(int);
tnode *addtree(tnode *, char *);
void treeprint(tnode *);
void treeprint_iter(tnode *);
int getword(char *, int, FILE *);
void join(tnode *, tnode *);
tnode *append(tnode *, tnode *);
tnode *treetolist(tnode *); 
void treeprint_postorder(tnode*);
void printpaths(tnode* node);
void _printpaths(tnode* node, char *, int pathLen);

/* defines */
#define MAXWORD 100
#define BUFSIZE 100 


int main(int argc, char **argv)
{
	tnode *root = NULL;
	char word[MAXWORD];
	FILE *fp = stdin;
	if ( argc == 2 ) 
		if (!(fp = fopen(argv[1], "r")))
			return 1;

	while (getword(word, MAXWORD, fp) != EOF)
			root = addtree(root, word);

	treeprint(root);
	printf("\n\n");
	treeprint_iter(root);
	printf("\n\n");

	printpaths(root);
	treeprint(root);
	printf("\n\n");
	treeprint_postorder(root);

	
	root = treetolist(root);
	tnode *o = root;
	tnode *last = NULL;
	for(o=root;o;o=o->large) 
	{
		printf("(%d %s))--> ", o->count, o->word);
		if (o == last)
			break;
		last = root;
	}
	printf("\n\n");
	return 0;
}

/* addtree: add a node with w, at or below p */
tnode *addtree(tnode *p, char *w)
{
	int cond;
	if (p == NULL) /* a new word has arrived */
	{ 
		p = malloc(sizeof(tnode));
		p->word = strdup(w);
		p->count = 1;
		p->small = p->large = NULL; 
	} 
	else if ((cond = strcmp(w, p->word)) == 0)
	{
		p->count++; 
	}
	else if (cond < 0)
	{ 
		p->small = addtree(p->small, w);
	}
	else
	{ 
		p->large = addtree(p->large, w);
	}
	return p;
}

void treeprint(tnode *p)
{
	/* recursive tree printing */
	if (p != NULL)
	{
		treeprint(p->small); 
		printf("\t%d %s\n", p->count, p->word); 
		treeprint(p->large);
	}
}

void treeprint_iter(tnode *root)
{
	/* Morris traversal */
	tnode *current,*pre; 
	if(root == NULL)
		return; 
	current = root;
	while(current != NULL)
	{				 
		if(current->small == NULL)
		{
			printf("\t%d %s\n", current->count, current->word);
			current = current->large;	  
		}	
		else
		{ 
			pre = current->small;
			while(pre->large != NULL && pre->large != current)
				pre = pre->large; 
			if(pre->large == NULL)
			{
				pre->large = current;
				current = current->small;
			} 
			else 
			{
				pre->large = NULL;
				printf("\t%d %s\n", current->count, current->word);
				current = current->large;	  
			}
		} 
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

void join(tnode *a, tnode *b)
{
	a->large = b;
	b->small = a;
}

tnode *append(tnode *a, tnode *b)
{
	tnode *aLast, *bLast;
	if (a==NULL) return(b);
	if (b==NULL) return(a);
	aLast = a->small;
	bLast = b->small;
	join(aLast, b);
	join(bLast, a);
	return(a);
}

tnode *treetolist(tnode *root)
{
	tnode *aList, *bList;
	if (root==NULL)
	return(NULL);

	aList = treetolist(root->small);
	bList = treetolist(root->large);
 
	root->small = root;
	root->large = root;
  
	aList = append(aList, root);
	aList = append(aList, bList);
	return(aList);
}

void treeprint_postorder(tnode* node)
{
	if (node == NULL)
		return; 
	static int i = 0;
	if (i == 0 && ++i )
	printf("\t[%s]\n", node->word);

	treeprint(node->small);
	printf("\n");
	treeprint(node->large);
	
}

void printpaths(tnode* node)
{
	char path[1000] = { 0 };
	_printpaths(node, path, 0);
} 

void _printpaths(tnode* node, char *path, int pathLen)
{
	if (node==NULL)
		return; 
	pathLen += sprintf(path + pathLen, "%s--> ", node->word);

	if (node->small == NULL && node->large==NULL) { 
		printf("%s\n", path);
	}
	else { 
		_printpaths(node->small, path, pathLen);
		_printpaths(node->large, path, pathLen);
	}
}

