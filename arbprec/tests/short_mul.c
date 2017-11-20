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
	short_mul2(a->number, temp + 1, a->len, b, base);
	//short_mul2(a->number, temp , a->len, b, base);
	arb_printold(a);
	printf("%d\n", b);
	//arb_short_mul(a->number, a->len, b, base);
	//short_mul2(a, a->len, b, 1, temp + 1 ,base);
	//arb_mul_core(a ,a->len, b, 1, temp + 1 ,base);
	ARBT ar[10] = { 0 };
	ar[0] = b;
	arb_mul_core(a->number, a->len, ar, 1, temp2 , base);
        
        for (size_t qq = 0; qq<a->len;++qq)
        {
                 printf("%d ", temp[qq]);
        }
        printf("\n");
	
        for (size_t qq = 0; qq<a->len;++qq)
        {
                 printf("%d ", temp2[qq]);
        }
        printf("\n");


	arb_short_mul(c->number, c->len, b, base);
        for (size_t qq = 0; qq<c->len;++qq)
        {
                 printf("%d ", c->number[qq]);
        }
        printf("\n");
	



	return 0;
}

