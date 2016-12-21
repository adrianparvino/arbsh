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

//#include "string.h" 

char *optarg; /* Global argument pointer. */
int optind = 0; /* Global argv index. */

static char *scan = NULL; /* Private scan pointer. */

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
	place = gstrchr(optstring, c);

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
