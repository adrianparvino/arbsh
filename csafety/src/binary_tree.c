#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* structures */
struct tnode { 
	char *word;
	int count;
	size_t depth;
	struct tnode *left;
	struct tnode *right;
};
 
/* prototypes */ 
int ngetch(FILE *); 
int getch(void);
void ungetch(int);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
void treeprint_iter(struct tnode *);
int getword(char *, int, FILE *);

/* defines */
#define MAXWORD 100
#define BUFSIZE 100

/* globals */
struct gchbuf{
	char buf[BUFSIZE]; /* buffer for ungetch */
	int bufp; /* next free position in buf */
}gchbuf = { {0}, 0 };

/* word frequency count */
int main(void)
{
	struct tnode *root = NULL;
	char word[MAXWORD];
	FILE *fp = fopen("data.txt", "r");
	if (!(fp))
		return 1;
	while (getword(word, MAXWORD, fp) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	
	treeprint(root);
	printf("\n\n");
	treeprint_iter(root);
	printf("\n\n");
	return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	if (p == NULL) /* a new word has arrived */
	{ 
		p = malloc(sizeof(struct tnode));
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL; 
	} 
	else if ((cond = strcmp(w, p->word)) == 0)
	{
		p->count++; 
	}
	else if (cond < 0)
	{ 
		p->left = addtree(p->left, w);
	}
	else
	{ 
		p->right = addtree(p->right, w);
	}
	return p;
}

void treeprint(struct tnode *p)
{
	/* recursive tree printing */
	if (p != NULL)
	{
		treeprint(p->left); 
		printf("\t%d %s\n", p->count, p->word); 
		treeprint(p->right);
	}
}

void treeprint_iter(struct tnode *root)
{
	/* Morris traversal */
	struct tnode *current,*pre; 
	if(root == NULL)
		return; 
	current = root;
	while(current != NULL)
	{                 
		if(current->left == NULL)
		{
			printf("\t%d %s\n", current->count, current->word);
			current = current->right;      
		}    
		else
		{ 
			pre = current->left;
			while(pre->right != NULL && pre->right != current)
				pre = pre->right; 
			if(pre->right == NULL)
			{
				pre->right = current;
				current = current->left;
			} 
			else 
			{
				pre->right = NULL;
				printf("\t%d %s\n", current->count, current->word);
				current = current->right;      
			}
		} 
	} 
}

int getword(char *word, int lim, FILE *fp)
{
	int c;
	char *w = word;
	while (isspace(c = ngetch(fp)))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c))
	{
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
	{
		if (!isalnum(*w = ngetch(fp)))
		{
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}

int ngetch(FILE *fp) /* get a (possibly pushed-back) character */
{
	return (gchbuf.bufp > 0) ? gchbuf.buf[--gchbuf.bufp] : fgetc(fp);
}

void ungetch(int c) /* push character back on input */
{
	if (gchbuf.bufp >= BUFSIZE)
		fprintf(stderr, "ungetch: too many characters\n");
	else
		gchbuf.buf[gchbuf.bufp++] = c;
}

