#include <arbprec/arbprec.h>
#include <stdlib.h>
#include <time.h>
#define MAXIMA 10000
#define BASE_MAX 10
                

char *make_bignum(size_t limit, int base)
{
	size_t truelim = random() % limit;
	char *ret;
	size_t i = 0;
	int sign;
	if (!(ret = malloc(truelim + 1)))
		return NULL;
	sign = (random() % 2);
        if (sign == 0)
                ret[i++] = '-';
	for(;i < truelim; i++)
                ret[i] = arb_highbase((random() % base));

	ret[(random() % truelim)] = '.';
	ret[i] = 0;
	return ret;
}

int main(int argc, char *argv[])
{

	if ( argc < 2)
	{
		printf("requires a test type, like 'div' or 'sub'\n");
		return 1;
	}
	char *string1 = make_bignum(MAXIMA, BASE_MAX);
	char *string2 = make_bignum(MAXIMA, BASE_MAX);
	
	size_t scale = random() % 10000;
	fprintf(stderr, "scale=%zu;\n", scale);
	if (strcmp(argv[1], "div") == 0)
		fprintf(stderr, "%s / %s\nquit\n", string1, string2);
	
	if (strcmp(argv[1], "add") == 0)
		fprintf(stderr, "%s + %s\nquit\n", string1, string2);
	
	if (strcmp(argv[1], "sub") == 0)
		fprintf(stderr, "%s - %s\nquit\n", string1, string2);
	
	if (strcmp(argv[1], "mul") == 0)
		fprintf(stderr, "%s * %s\nquit\n", string1, string2);
	
	if (strcmp(argv[1], "mod") == 0)
		fprintf(stderr, "%s %% %s\nquit\n", string1, string2);

	fxdpnt *a, *b, *c;
	a = arb_str2fxdpnt(string1);
	b = arb_str2fxdpnt(string2);
	c = arb_expand(NULL, MAXIMA*2);
	
	if (strcmp(argv[1], "div") == 0)
		c = arb_alg_d(a, b, c, 10, scale);
	
	if (strcmp(argv[1], "add") == 0)
		c = arb_add(a, b, c, 10);
	
	if (strcmp(argv[1], "sub") == 0)
		c = arb_sub(a, b, c, 10);
	
	if (strcmp(argv[1], "mul") == 0)
		c = arb_mul(a, b, c, 10, scale);

	if (strcmp(argv[1], "mod") == 0)
		c = arb_mod(a, b, c, 10, scale);
	
	arb_print(c);
	arb_free(a);
	arb_free(b);
	arb_free(c);
	return 0;
}

