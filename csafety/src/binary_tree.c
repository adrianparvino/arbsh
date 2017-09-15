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
typedef struct bstnode { 
	char *word;
	size_t count;
	struct bstnode *small;/* left */
	struct bstnode *large;/* right */
}bstnode;
 
/* prototypes */ 
int ngetch(FILE *); 
int getch(void);
void ungetch(int);
bstnode *addtree(bstnode *, char *);
void treeprint(bstnode *);
void treeprint_iter(bstnode *);
int getword(char *, size_t, FILE *);
void join(bstnode *, bstnode *);
bstnode *append(bstnode *, bstnode *);
bstnode *treetolist(bstnode *); 
void treeprint_postorder(bstnode*);
void bst_printpaths(bstnode* node);
void _bst_printpaths(bstnode* node, char *, size_t, size_t); 

int main(int argc, char **argv)
{
	bstnode *root = NULL;
	char word[100];
	FILE *fp = stdin;
	if ( argc == 2 ) 
		if (!(fp = fopen(argv[1], "r")))
			return 1;

	while (getword(word, 100, fp) != EOF)
			root = addtree(root, word);

	treeprint(root);
	printf("\n\n");
	treeprint_iter(root);
	printf("\n\n");

	bst_printpaths(root);
	treeprint(root);
	printf("\n\n");
	treeprint_postorder(root);

	
	root = treetolist(root);
	bstnode *o = root;
	bstnode *last = NULL;
	for(o=root;o;o=o->large) 
	{
		printf("(%zu %s))--> ", o->count, o->word);
		if (o == last)
			break;
		last = root;
	}
	printf("\n\n");
	return 0;
}

/* addtree: add a node with w, at or below p */
bstnode *addtree(bstnode *p, char *w)
{
	int cond;
	if (p == NULL) /* a new word has arrived */
	{ 
		p = malloc(sizeof(bstnode));
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

void treeprint(bstnode *p)
{
	/* recursive tree printing */
	if (p != NULL)
	{
		treeprint(p->small); 
		printf("\t%zu %s\n", p->count, p->word); 
		treeprint(p->large);
	}
}

void treeprint_iter(bstnode *root)
{
	/* Morris traversal */
	bstnode *current,*pre; 
	if(root == NULL)
		return; 
	current = root;
	while(current != NULL)
	{				 
		if(current->small == NULL)
		{
			printf("\t%zu %s\n", current->count, current->word);
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
				printf("\t%zu %s\n", current->count, current->word);
				current = current->large;	  
			}
		} 
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

void join(bstnode *a, bstnode *b)
{
	a->large = b;
	b->small = a;
}

bstnode *append(bstnode *a, bstnode *b)
{
	bstnode *aLast, *bLast;
	if (a==NULL) return(b);
	if (b==NULL) return(a);
	aLast = a->small;
	bLast = b->small;
	join(aLast, b);
	join(bLast, a);
	return(a);
}

bstnode *treetolist(bstnode *root)
{
	bstnode *aList, *bList;
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

void treeprint_postorder(bstnode* node)
{
	if (node == NULL)
		return; 
	static int i = 0;
	if (i == 0 && ++i)
		printf("\t[%s]\n", node->word);
	treeprint(node->small);
	printf("\n");
	treeprint(node->large);
}

void bst_printpaths(bstnode* node)
{ 
	char path[1024] = { 0 };
	_bst_printpaths(node, path, 0, 1024);
} 

void _bst_printpaths(bstnode* node, char *p, size_t len, size_t lim)
{ 
	if (node==NULL)
		return; 
	char *n = node->word;
	len += snprintf(p+len, len-lim, "\"%s\"--> ", n);
	if ( len == lim)
		{ fprintf(stderr, "word is too large\n"); return;}
	if (node->small == NULL && node->large==NULL) { 
		printf("%s\n", p);
	}
	else { 
		_bst_printpaths(node->small, p, len, lim);
		_bst_printpaths(node->large, p, len, lim);
	}
}

