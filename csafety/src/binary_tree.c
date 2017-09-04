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
void treeprint(struct tnode *, char *);
int getword(char *, int, FILE *);
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
	// "now is the time for all good men to come to the aid of their party"
	
	struct tnode *root;
	char word[MAXWORD];
	root = NULL;
	FILE *fp;

	fp = fopen("data.txt", "r");
	//while (fgets(fp) != NULL)
		
	while (getword(word, MAXWORD, fp) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	
	treeprint(root, "start");
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
void treeprint(struct tnode *p, char *s)
{
	int depth = 10;
	if (p != NULL)
	{
		treeprint(p->left, "left");
		if (!(strcmp(s, "start")))
			depth = 5; 
		printf("%.*s %4d %s   %s --> \n", depth, "                      ", p->count, p->word, s); 
		
		if (p->right && p->right->word)
		printf("         %.*s %s       %s --> \n", depth, "                      ", p->right->word, s); 
		if (p->left && p->left->word)
		printf("         %.*s %s       %s --> \n", depth, "                      ", p->left->word, s); 
		
		if (!(strcmp(s, "start")))
			depth = 10;
		treeprint(p->right, "right");
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
	return (bufp > 0) ? buf[--bufp] : fgetc(fp);
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		fprintf(stderr, "ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

