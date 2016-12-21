#include "lib/cutils.h"
struct nlist {     /* table entry: */
        struct nlist *next;   /* next entry in chain */
        char *name;                /* defined name */
        char *defn;                /* replacement text */
};
#define HASHSIZE 1000
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *s)
{
        /* hash: form hash value for string s */
        unsigned hashval;
        for (hashval = 0; *s != '\0'; s++)
                hashval = *s + 31 * hashval;
        return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
        /* lookup: look for s in hashtab */
        struct nlist *np;
        for (np = hashtab[hash(s)]; np != NULL; np = np->next)
                if (strcmp(s, np->name) == 0)
                        return np;       /* found */
        return NULL;               /* not found */
}
struct nlist *lookup(char *);


struct nlist *install(char *name, char *defn)
{
        /* install: put (name, defn) in hashtab */
        struct nlist *np;
        unsigned hashval;
        if ((np = lookup(name)) == NULL) { /* not found */
                np = (struct nlist *) malloc(sizeof(*np));
                if (np == NULL || (np->name = strdup(name)) == NULL)
                        return NULL;
                hashval = hash(name);
                np->next = hashtab[hashval];
                hashtab[hashval] = np;
        } else     /* already there */
                free((void *) np->defn);   /*free previous defn */
        if ((np->defn = strdup(defn)) == NULL)
                return NULL;
        return np;
}

