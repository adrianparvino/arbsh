#include <arbprec/arbprec.h>
#include <stdlib.h>
#include <time.h>
#define MAXIMA 10000
int main(int argc, char *argv[])
{

	if ( argc < 2)
	{
		printf("requires a test type, like 'div' or 'sub'\n");
		return 1;
	}
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
	if (strcmp(argv[1], "div") == 0)
		fprintf(stderr, "%s / %s\nquit\n", string1, string1);
	
	if (strcmp(argv[1], "add") == 0)
		fprintf(stderr, "%s + %s\nquit\n", string1, string1);
	
	if (strcmp(argv[1], "sub") == 0)
		fprintf(stderr, "%s - %s\nquit\n", string1, string1);
	
	if (strcmp(argv[1], "mul") == 0)
		fprintf(stderr, "%s * %s\nquit\n", string1, string1);

	fxdpnt *a;
	a = arb_str2fxdpnt(string1);


	
	if (strcmp(argv[1], "div") == 0)
		a = arb_alg_d(a, a, a, 10, scale);
	
	if (strcmp(argv[1], "add") == 0)
		a = arb_add(a, a, a, 10);
	
	if (strcmp(argv[1], "sub") == 0)
		a = arb_sub(a, a, a, 10);
	
	if (strcmp(argv[1], "mul") == 0)
		a = arb_mul(a, a, a, 10, scale);
	
	arb_print(a);
	arb_free(a);


	return 0;
}

