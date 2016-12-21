/* Numerical binary search tree */
struct nbinnode {
        int word;
        int count;
        struct nbinnode *left;
        struct nbinnode *right;
};
struct nbinnode *nbinalloc(void);
struct nbinnode *nbinsearch(struct nbinnode *p, int w, int *hasword)
{
        hasword[0] = 0;

        if (p == NULL) {
                p = nbinalloc();
                p->word = w;
                p->count = 1;
                p->left = p->right = NULL;
        }
        else if (w == p->word)
        {
                p->count++;
                hasword[0] = 1;
        }
        else if ( w < p->word)
                p->left = nbinsearch(p->left, w, hasword);
        else
                p->right = nbinsearch(p->right, w, hasword);

        return p;
}

struct nbinnode *nbinalloc(void)
{
       return (struct nbinnode *) malloc(sizeof(struct nbinnode));
}

void nbinfree(struct nbinnode *p)
{
        if (p != NULL) {
                nbinfree(p->left);
                nbinfree(p->right);
                free(p->right);
                free(p->left);
        }

}
/* end */


/* string binary search tree */
struct tnode {
        char *word;
        int count;
        struct tnode *left;
        struct tnode *right;
};
struct tnode *addtree(struct tnode *, char *, int *);
struct tnode *talloc(void);
void treefree(struct tnode *);

struct tnode *addtree(struct tnode *p, char *w, int *hasword)
{
        hasword[0] = 0;
        int cond = 0;
        if (p == NULL) {
                p = talloc();
                if (!(p))
                        return NULL;
                p->word = strdup(w);
                p->count = 1;
                p->left = p->right = NULL;
        }
        else if ((cond = strcmp(w, p->word)) == 0)
        {
                p->count++;
                hasword[0] = 1;

        }
        else if (cond < 0)
                p->left = addtree(p->left, w, hasword);
        else
                p->right = addtree(p->right, w, hasword);

        return p;
}


struct tnode *talloc(void)
{
       return (struct tnode *) malloc(sizeof(struct tnode));
}

void treefree(struct tnode *p)
{
        if (p != NULL) {
                treefree(p->left);
                free(p->word);
                treefree(p->right);
                free(p->right);
                free(p->left);
        }
}

