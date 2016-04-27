/* inode tracking table for du */
struct nlist {
        struct nlist *next;
        int inode;
} nlist;

#define HASHSIZE 1011111 

struct nlist *hashtab[HASHSIZE ];

unsigned hash(int inode)
{
        return (inode + 31) % HASHSIZE;
}

struct nlist *lookup(int inode)
{
        struct nlist *np;
        for (np = hashtab[hash(inode)]; np != NULL; np = np->next)
                if ( inode == np->inode )
                        return np;
        return NULL;
}

int install(int inode)
{
        struct nlist *np;
        if ((np = lookup(inode)) == NULL)
        {
                if (!(np = (struct nlist *) malloc(sizeof(*np)) ))
                        return 1;
                np->inode = inode;
                np->next = hashtab[hash(inode)];
                hashtab[hash(inode)] = np;
        }
        return 0;
}
/* end */

