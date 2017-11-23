#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{
        if (argc < 5)
        {
                printf("needs 4 args: bignum bignum   base  scale\n");
                return 0;
        }
	
        int base = strtol(argv[3],0,  10);
        int scale =  strtol(argv[4],0,  10);
	fxdpnt *a = NULL;
	fxdpnt *c = NULL;
	a = arb_expand(a, 1);
	c = arb_expand(c, 100);
        a = arb_str2fxdpnt(argv[1]);
        arb_babylonian_sqrt(a, c, 10, 100);
        arb_print(c);
        return 0;
}

