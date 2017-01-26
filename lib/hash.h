#define HASHSIZE 10000

/* structures */
struct snlist {     /* table entry: */
	struct snlist *next;   /* next entry in chain */
	char *name;		/* defined name */
	char *defn;		/* replacement text */
};

struct inlist {    
	struct inlist *next;  
	int name;
	int defn;
};

static struct snlist *shashtab[HASHSIZE]; /* pointer table */
static struct inlist *ihashtab[HASHSIZE]; 

/* function prototypes */
unsigned shash(char *);
unsigned ihash(int);
struct snlist *slookup(char *);
struct inlist *ilookup(int);
struct snlist *sinstall(char *, char *);
struct inlist *iinstall(int, int);

/* functions */
unsigned shash(char *s)
{
	unsigned shashval;
	for (shashval = 0; *s != '\0'; s++)
		shashval = *s + 31 * shashval;
	return shashval % HASHSIZE;
}

unsigned ihash(int s)
{
	unsigned ihashval = 1;
	ihashval = s + 31 * ihashval;
	return ihashval % HASHSIZE;
} 

struct snlist *slookup(char *s)
{
	struct snlist *np;
	for (np = shashtab[shash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

struct inlist *ilookup(int s)
{
	struct inlist *np;
	for (np = ihashtab[ihash(s)]; np != NULL; np = np->next)
		if ( s == np->name )
			return np;
	return NULL;
} 

struct snlist *sinstall(char *name, char *defn)
{
	struct snlist *np;
	unsigned shashval;
	if ((np = slookup(name)) == NULL)
	{
		np = malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		shashval = shash(name);
		np->next = shashtab[shashval];
		shashtab[shashval] = np;
	} else
		free(np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
} 

struct inlist *iinstall(int name, int defn)
{
	struct inlist *np;
	unsigned ihashval;
	if ((np = ilookup(name)) == NULL)
	{
		np = malloc(sizeof(*np));
		if (np == NULL || (np->name = name) == 0 )
			return NULL; 
		if (np == NULL )
			return NULL;
		np->name = name;
		ihashval = ihash(name);
		np->next = ihashtab[ihashval];
		ihashtab[ihashval] = np;
	} else
		{}; //free(np->defn);  
	np->defn = defn; 
	return np;
}
