#include <arbprec/arbprec.h>
#include <stdlib.h>
#include <time.h>
#define MAXIMA 10000
int main(void)
{

	size_t i = 0;

	srandom(time(NULL));

	size_t MAXIMA1 = (random() % MAXIMA);
	size_t MAXIMA2 = (random() % MAXIMA);
	
	char *string1 = malloc(MAXIMA1 + 1);
	char *string2 = malloc(MAXIMA2 + 1);
	
	if (!string1 || !string2)
		return 1;


	while ( i < MAXIMA1 )
	{
		string1[i] = (random() % 10) + '0';
		++i;
	}
	string1[i] = 0;
	i = 0;
	while ( i < MAXIMA2 )
	{
		string2[i] = (random() % 10) + '0';
		++i;
	}
	string1[(random() % MAXIMA1)] = '.';
	string2[(random() % MAXIMA2)] = '.';
	
	string2[i] = 0;
	size_t scale = random() % 10000;
	fprintf(stderr, "scale=%zu;\n", scale);
	fprintf(stderr, "%s/%s\nquit\n", string1, string2);
	fxdpnt *a, *b, *c;
	a = arb_str2fxdpnt(string1);
	b = arb_str2fxdpnt(string2);
	c = arb_expand(NULL, MAXIMA*2);
	c = arb_alg_d(a, b, c, 10, scale);
	arb_print(c);
	arb_free(a);
	arb_free(b);
	arb_free(c);
	return 0;
}

