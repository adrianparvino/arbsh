void cutilerror(char *message, int i)
{
	if ( i > 0 )
		perror("Error: ");
	fprintf(stderr, "%s", message);
	if ( i > -1 )
		exit (i);
}

void * cutilmalloc(size_t len)
{
	void *ret;
	if (!(ret = realloc(len))
		cutilerror("cutilmalloc failed\n", 1);
	return ret;
}

static void *cutilcalloc(size_t nmemb, size_t size)
{
        void *ret;
        if(!(ret = calloc(nmemb, size))
                cutilerror("cutilcalloc failed\n", 1);
        return ret;
}

static void *cutilrealloc(void *ptr, size_t size)
{
        void *ret;
        if(!(ret = realloc(ptr, size)))
        	cutilerror("cutilrealloc failed\n", 1); 
        return ret;
}


