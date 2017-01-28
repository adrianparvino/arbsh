/*
 * This is a version of the public domain getopt implementation by
 * Henry Spencer originally posted to net.sources.
 *
 * This file is in the public domain.
 * 
 *
 *
 * Modified by CM Graff for GrafOS 
 */ 


char *optarg; 			/* Global argument pointer. */
int optind = 0;			/* Global argv index. */

static char *scan = NULL;	/* Private scan pointer. */

int ggetopt(int argc, char *argv[], char *optstring)
{
	char c;
	char *place;

	optarg = NULL;

	if (!scan || *scan == '\0') 
	{
		if (optind == 0)
			optind++;

		if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0')
				return EOF;
		if (argv[optind][1] == '-' && argv[optind][2] == '\0')
		{
			optind++;
			return EOF;
		}

		scan = argv[optind]+1;
		optind++;
	}

	c = *scan++;
	place = strchr(optstring, c);

	if (!place || c == ':') 
		return '?';


	place++;
	if (*place == ':') {
		if (*scan != '\0') {
			optarg = scan;
			scan = NULL;
		} else if( optind < argc ) {
			optarg = argv[optind];
			optind++;
		} else { 
			write(2, "option requires argument\n", 27);
			return ':';
		}
	}

	return c;
}




#ifdef __NR_brk
void* gsbrk(intptr_t x)
{
	void *new;
	void *old;

	old = (void *)syscall(__NR_brk, 0);

	new = (void *)syscall(__NR_brk, ((uintptr_t)old) + x);

	if ( (((uintptr_t)new) == (((uintptr_t)old) + x)) )
		return old;

	return (void *)-1;
}
#endif

