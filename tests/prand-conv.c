#include <arbprec/arbprec.h>
#include <stdlib.h>
#include <time.h>
#define MAXIMA 100
int main(int argc, char *argv[])
{

	size_t i = 0;

	srandom(time(NULL));

	size_t MAXIMA1 = (random() % MAXIMA);

	
	char *string1 = malloc(MAXIMA1 + 1);

	
	if (!string1)
		return 1;


	while ( i < MAXIMA1 )
	{
		string1[i] = (random() % 10) + '0';
		++i;
	}
	string1[i] = 0;

	string1[(random() % MAXIMA1)] = '.';

	size_t scale = random() % 10000;
	fprintf(stderr, "scale=%zu;\n", scale);
	
	
		

	fxdpnt *a;
	a = arb_str2fxdpnt(string1);
	fxdpnt *b = arb_expand(NULL, a->len);

	int base = 0;
	while ( base <2 || (base > 10 && base < 16))
	{
		base = random() % 16;
		//printf("finding scale\n");
	}
	fprintf(stderr, "ibase=10;obase=%d;%s+0\nquit\n", base, string1);
	a = convscaled(a, b, 10, base);
	
	arb_print(b);
	arb_free(a);


	return 0;
}

