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
        fxdpnt *a = arb_new_num(12, scale);
	fxdpnt *b = NULL;

	b = arb_expand(b, 1);
        fxdpnt *c = arb_new_num(12, scale);
        a = arb_str2fxdpnt(argv[1]);
        b = arb_str2fxdpnt(argv[2]);
	c = arb_alg_d(a, b, c, base, scale);
        arb_print(c);
        return 0;
}

