#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* structures */
struct tnode { 
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

/* prototypes */
int getch(void);
void ungetch(int);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);

/* defines */
#define MAXWORD 100
#define BUFSIZE 100

/* globals */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* word frequency count */
int main(void)
{
	struct tnode *root;
	char word[MAXWORD];
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	if (p == NULL) {
		/* a new word has arrived */
		p = talloc();
		/* make a new node */
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
		/* repeated word */
	else if (cond < 0)
		/* less than into left subtree */
		p->left = addtree(p->left, w);
	else
		/* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;

}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return malloc(sizeof(struct tnode));
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

int getword(char *word, int lim)
{
	int c;
	char *w = word;
	while (isspace(c = getch()))
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
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
} 

int getch(void) /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		fprintf(stderr, "ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

