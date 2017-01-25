struct nlist {     /* table entry: */
        struct nlist *next;   /* next entry in chain */
        int name;
        int defn;
};
#define HASHSIZE 10000
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(int s)
{
        unsigned hashval = 1;
        hashval = s + 31 * hashval;
        return hashval % HASHSIZE;
}

struct nlist *lookup(int s)
{
        struct nlist *np;
        for (np = hashtab[hash(s)]; np != NULL; np = np->next)
                if ( s == np->name )
                        return np;
        return NULL;
}

struct nlist *install(int name, int defn)
{
        struct nlist *np;
        unsigned hashval;
        if ((np = lookup(name)) == NULL) {
                np = (struct nlist *) malloc(sizeof(*np));
              if (np == NULL || (np->name = name) == 0 )
                      return NULL; 
              if (np == NULL )
                        return NULL;
                np->name = name;
                hashval = hash(name);
                np->next = hashtab[hashval];
                hashtab[hashval] = np;
        } else  free((void *) np->defn);  
      np->defn = defn; 
        return np;
}
