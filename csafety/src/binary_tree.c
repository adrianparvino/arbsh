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
	struct bstnode *small;/* left/prev */
	struct bstnode *large;/* right/next */
}bstnode;

/* prototypes */
size_t bst_maxdepth(bstnode *);
void treefree(bstnode *);
bstnode *bst_add(bstnode *, char *);
void bst_print(bstnode *);
void bst_print_iter(bstnode *);
void bst_preorder(bstnode*);
int getword(char *, size_t, FILE *);
void bst_join(bstnode *, bstnode *);
bstnode *bst_append(bstnode *, bstnode *);
bstnode *bst_to_list(bstnode *);
void bst_printpaths(bstnode *);
void _bst_printpaths(bstnode *, char *, size_t, size_t); 
void bst_inorder(bstnode *);
void bst_post(bstnode *);


int main(int argc, char **argv)
{
	bstnode *root = NULL;
	char word[100];
	FILE *fp = stdin;
	if ( argc == 2 ) 
		if (!(fp = fopen(argv[1], "r")))
			return 1;

	while (getword(word, 100, fp) != EOF)
			root = bst_add(root, word);


	bst_print(root);
	printf("\n\n");
	bst_print_iter(root);
	printf("\n\n");
	bst_printpaths(root);
	bst_print(root);
	printf("\n\nin\n");
	bst_inorder(root);
	printf("\n\npost\n");
	bst_post(root);
	
	printf("\n\npre\n");
	bst_preorder(root);
	/*
	root = bst_to_list(root);
	bstnode *o = root;
	bstnode *last = NULL;
	for(o=root;o;o=o->large) 
	{
		printf("(%zu %s))--> ", o->count, o->word);
		if (o == last)
			break;
		last = root;
	}
	*/
	treefree(root);
	free(root);
	printf("\n\n");
	if (fp!=stdin)fclose(fp);
	return 0;
}

/* bst_add: add a node with w, at or below p */
bstnode *bst_add(bstnode *p, char *w)
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
		p->count++;
	else if (cond < 0)
		p->small = bst_add(p->small, w);
	else 
		p->large = bst_add(p->large, w);
	return p;
}

void bst_print(bstnode *p)
{
	/* recursive tree printing */
	if (p != NULL)
	{
		bst_print(p->small); 
		printf("\t%zu %s\n", p->count, p->word); 
		bst_print(p->large);
	}
}

void bst_print_iter(bstnode *root)
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

void bst_join(bstnode *a, bstnode *b)
{
	a->large = b;
	b->small = a;
}

bstnode *bst_append(bstnode *a, bstnode *b)
{
	bstnode *aLast, *bLast;
	if (a==NULL) return(b);
	if (b==NULL) return(a);
	aLast = a->small;
	bLast = b->small;
	bst_join(aLast, b);
	bst_join(bLast, a);
	return(a);
}

bstnode *bst_to_list(bstnode *root)
{
	bstnode *aList, *bList;
	if (root==NULL)
		return(NULL);

	aList = bst_to_list(root->small);
	bList = bst_to_list(root->large);
 
	root->small = root;
	root->large = root;
  
	aList = bst_append(aList, root);
	aList = bst_append(aList, bList);
	return(aList);
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

void treefree(bstnode *p)
{
	if (p == NULL)
		return;
	treefree(p->small);
	free(p->word);
	treefree(p->large);
	free(p->large);
	free(p->small);
}

size_t bst_maxdepth(bstnode *p)
{
	size_t small, large;
	if (p == NULL)
		return 0;
	
	small = bst_maxdepth(p->small);
	large = bst_maxdepth(p->large); 
	if (small > large) 
		return(small + 1);
	else 
		return(large + 1);
}

void bst_inorder(bstnode* p)
{
	if (p == NULL)
		return;
	bst_inorder(p->small);
	printf("%s ", p->word);
	bst_inorder(p->large);
}

void bst_post(bstnode* p)
{
	if (p == NULL)
		return; 
	bst_post(p->small); 
	bst_post(p->large);
	printf("%s ", p->word);
}

void bst_preorder(bstnode* p)
{
	if (p == NULL)
		return;
	printf("%s ", p->word);
	bst_preorder(p->small);
	bst_preorder(p->large);
}

