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
void MorrisTraversal(struct tnode *root)
{
  struct tnode *current,*pre;
 
  if(root == NULL)
     return; 
 
  current = root;
  while(current != NULL)
  {                 
    if(current->left == NULL)
    {
      printf("%s ", current->word);
      current = current->right;      
    }    
    else
    {
      /* Find the inorder predecessor of current */
      pre = current->left;
      while(pre->right != NULL && pre->right != current)
        pre = pre->right;
 
      /* Make current as right child of its inorder predecessor */
      if(pre->right == NULL)
      {
        pre->right = current;
        current = current->left;
      }
             
      /* Revert the changes made in if part to restore the original 
        tree i.e., fix the right child of predecssor */   
      else 
      {
        pre->right = NULL;
        printf("%s ",current->word);
        current = current->right;      
      } /* End of if condition pre->right == NULL */
    } /* End of if condition current->left == NULL*/
  } /* End of while */
}
 
/* prototypes */ 
int ngetch(FILE *); 
int getch(void);
void ungetch(int);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
void treeprint_inter(struct tnode *);
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
	MorrisTraversal(root);
	return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	
	

	if (p == NULL) /* a new word has arrived */
	{
	//	printf("N %s\n", w);
		
		p = malloc(sizeof(struct tnode));
		p->word = strdup(w); /* make a new node */
		p->count = 1;
		p->left = p->right = NULL;
	//	fflush(stdout);
		//printf("  P %s\n", p->word);
	} 
	else if ((cond = strcmp(w, p->word)) == 0) /* repeated word */ 
	{
		p->count++; 
	}
	else if (cond < 0) /* less than into left subtree */
	{ 
		//printf("  P %s\n", p->word);
		//printf("        L %s\n", w);
		
		//printf("        L %s\n", p->word);
		//fflush(stdout);
		p->left = addtree(p->left, w);
	}
	else /* greater than into right subtree */
	{ 
		//printf("  P %s\n", p->word);
		//printf("                R %s\n", w);
		//printf("                R %s\n", p->word);
		//fflush(stdout);
		p->right = addtree(p->right, w);
	}
	return p;

} 

void treeprint_inter(struct tnode *p)
{
	int depth = 10;
	struct tnode *o = p;
	if (p != NULL)
	{
		while (p && o)
		{ 
		        if (p->left)
			{ 
				p = p->left;
				printf("%4d %s\n", p->count, p->word); 
				o = p;
			}
			
			
		        if (o->right)
			{
				printf("%4d %s\n",o->count, o->word);
				o = o->right;
				p = o;
			}
			
		}
	//	treeprint(p->left); 
		//printf("%.*s %4d %s\n", depth, "     ", p->count, p->word); 
	//	treeprint(p->right);
	}
}
/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	int depth = 10;
	if (p != NULL)
	{
		treeprint(p->left); 
		printf("%.*s %4d %s\n", depth, "     ", p->count, p->word); 
		treeprint(p->right);
	}
}
void treeprint2(struct tnode *p, char *s)
{
	int depth = 10;
	if (p != NULL)
	{
		treeprint2(p->left, "left");
		if (!(strcmp(s, "start")))
			depth = 5; 
		printf("%.*s %4d %s   %s --> \n", depth, "                      ", p->count, p->word, s); 
		
		if (p->right && p->right->word)
		printf("         %.*s %s       %s --> \n", depth, "                      ", p->right->word, s); 
		if (p->left && p->left->word)
		printf("         %.*s %s       %s --> \n", depth, "                      ", p->left->word, s); 
		
		if (!(strcmp(s, "start")))
			depth = 10;
		treeprint2(p->right, "right");
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

