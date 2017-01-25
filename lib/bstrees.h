/* structures */
struct tnode {
        char *word;
        int count;
        struct tnode *left;
        struct tnode *right;
};

/* function prototypes */
struct tnode *addtree(struct tnode *, char *, int *);
void treefree(struct tnode *);

/* functions */
struct tnode *addtree(struct tnode *p, char *w, int *hasword)
{

        hasword[0] = 0;
        int cond = 0;
        if (p == NULL) {
		p = malloc(sizeof(struct tnode));
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

