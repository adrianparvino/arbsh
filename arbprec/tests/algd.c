#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{
        if (argc < 5)
        {
                printf("needs 4 args: bignum bignum   base  scale\n");
                return 0;
        }
	//verbosity = 1;
        int base = strtol(argv[3],0,  10);
        int scale =  strtol(argv[4],0,  10);
        //fxdpnt *a = arb_create(12, scale);
	fxdpnt *a = NULL;
	fxdpnt *b = NULL;
	a = arb_expand(a, 1);
	b = arb_expand(b, 1);
        fxdpnt *c = arb_create(12, scale);
	//c = arb_expand(c, scale);
	
	arb_init(c);
        a = arb_str2fxdpnt(argv[1]);
        b = arb_str2fxdpnt(argv[2]);
	c = arb_alg_d(a, b, c, base, scale);
        arb_print(c);
        return 0;
}

