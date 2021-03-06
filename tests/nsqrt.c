#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{
        if (argc < 4)
        {
                printf("needs 3 args: bignum base scale\n");
                return 0;
        }

        int base = strtol(argv[2],0, 10);
        int scale =  strtol(argv[3],0, 10);
	fxdpnt *a = NULL;
	fxdpnt *c = NULL;
	c = arb_expand(c, 10000);
        a = arb_str2fxdpnt(argv[1]);
	c = arb_newton_sqrt(a, c, base, scale);
        arb_print(c);
	arb_free(a);
	arb_free(c);
        return 0;
}

