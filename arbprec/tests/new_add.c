#include <arbprec/arbprec.h>

int main(int argc, char *argv[])
{
        if (argc < 4)
        {
                printf("needs 3 args: bignum bignum base\n");
                return 0;
        }
	
        int base = strtol(argv[3],0,  10);
	fxdpnt *a = NULL;
	fxdpnt *b = NULL;
	fxdpnt *c = NULL;
	//a = arb_expand(a, 1);
	//b = arb_expand(b, 1);
	c = arb_expand(c, 1);
	//arb_init(c);
        a = arb_str2fxdpnt(argv[1]);
        b = arb_str2fxdpnt(argv[2]);
	c = new_addition(a, b, c, base);
        arb_print(c);
        return 0;
}

