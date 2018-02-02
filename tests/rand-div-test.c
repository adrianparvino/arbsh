#include <arbprec/arbprec.h>
#include <stdlib.h>
#include <time.h>
#define MAXIMA 10000
int main(void)
{

	char *string1 = malloc(MAXIMA + 1);
	char *string2 = malloc(MAXIMA + 1);

	size_t i = 0;

	srandom(time(NULL));// this does not need to be time seed
	// srand(time(NULL));

	while ( i < MAXIMA )
	{
		string1[i] = (random() % 10) + '0';
		++i;
	}
	i = 0;
	while ( i < MAXIMA )
	{
		string2[i] = (random() % 10) + '0';
		++i;
	}
	string1[(random() % MAXIMA)] = '.';
	string2[(random() % MAXIMA)] = '.';
	string1[i] = 0;
	string2[i] = 0;
	size_t scale = random() % 100;
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

