/* globals */
static int numbuckets = 4096;		/* number of buckets */
static int prime = 0;			/* selector for prime number choice */
static int domain = 0;

/* A few commonly used primes */
size_t primes[9] = {
	31, 
	62,
	237,
	251,
	65521,
	131071,
	262139,
	524287,
	1327144009
};

/* numbuckets * prime = domain */
/* 1024 * 31 = 31744 ; 31744 bucket indices are reduced to 1024 buckets  */

/* structures */
struct snlist {			/** table entries **/
	struct snlist *next;	/* next entry in chain */
	char *name;		/* defined name */
	char *defn;		/* replacement text */
};

struct inlist {    
	struct inlist *next;  
	int name;
	int defn;
};

/* TODO: Dynamically allocate the pointer table */
static struct snlist *shashtab[4096];
static struct inlist *ihashtab[4096]; 

/* function prototypes */
unsigned shash(char *);
unsigned ihash(int);
struct snlist *slookup(char *);
struct inlist *ilookup(int);
struct snlist *sinstall(char *, char *);
struct inlist *iinstall(int, int);

void inithash(void)
{
	/* this is just for diagnostic */
	domain = numbuckets * primes[prime]; 
	
}

/*	
	TODO: Combine numeric and string hashing functions 
	using function pointers.
*/

/* functions */
unsigned shash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + primes[prime] * hashval;
	return hashval % numbuckets;
}

unsigned ihash(int s)
{
	unsigned hashval = 1;
	hashval = s + primes[prime] * hashval;
	return hashval % numbuckets;
} 

struct snlist *slookup(char *s)
{
	struct snlist *np;
	for (np = shashtab[shash(s)]; np != NULL; np = np->next)
		if (gstrcmp(s, np->name) == 0)
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
	unsigned hashval;
	if ((np = slookup(name)) == NULL)
	{
		np = malloc(sizeof(*np));
		if (np == NULL || (np->name = gstrdup(name)) == NULL)
			return NULL;
		hashval = shash(name);
		np->next = shashtab[hashval];
		shashtab[hashval] = np;
	} else
		free(np->defn);
	if ((np->defn = gstrdup(defn)) == NULL)
		return NULL;
	return np;
} 

struct inlist *iinstall(int name, int defn)
{
	struct inlist *np;
	unsigned hashval;
	if ((np = ilookup(name)) == NULL)
	{
		np = malloc(sizeof(*np));
		if (np == NULL || (np->name = name) == 0 )
			return NULL; 
		if (np == NULL )
			return NULL;
		np->name = name;
		hashval = ihash(name);
		np->next = ihashtab[hashval];
		ihashtab[hashval] = np;
	} else
		{}; //free(np->defn);  
	np->defn = defn; 
	return np;
}
