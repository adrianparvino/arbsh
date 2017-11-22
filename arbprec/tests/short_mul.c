#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{
	if (argc < 5 )
		arb_error("Needs 4 args, such as:  123 / 123 base scale");
 
	size_t scale =  strtol(argv[4], 0, 10);
	int base = strtol(argv[4], 0, 10);
	fxdpnt *a, *c;

	a = arb_str2fxdpnt(argv[1]);
	c = arb_str2fxdpnt(argv[2]);
	ARBT 	b = strtol(argv[3], 0, 10);
	ARBT temp[100] = { 0 };
	ARBT temp2[100] = { 0 };

	short_mul2(a->number, temp  +1, a->len, b, base);
	arb_printold(a);
	printf("%d\n", b);
	ARBT ar[10] = { 0 };
	ar[0] = b;
	arb_mul_core(a->number, a->len, ar, 1, temp2 , base);
        
	print_arbt(stderr, "temp = ", temp, a->len); 
	print_arbt(stderr, "arb_mul = ", temp2, a->len); 


        printf("\n");
	return 0;
}

