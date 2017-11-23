#include <arbprec/arbprec.h>
fxdpnt *arb_babylonian_sqrt(fxdpnt *x, fxdpnt *c, int base, int scale)
{
        // This function is provided to test the effectiveness of the division
        // and subtraction routines. It is not intended to be a performant sqrt
        size_t i = 0;
        arb_init(c);
	printf("x->len  %d\n", x->len);
        c = arb_expand(c, c->len + x->len);
	memset(c->number, 0, x->len * sizeof(ARBT));
        memcpy(c->number, x->number, x->len * sizeof(ARBT));
	

        c->len = x->len;
        fxdpnt *two = arb_str2fxdpnt("2.00000000000000000000000000000000000000000000000000000000000000000000");
        fxdpnt *sum = arb_expand(NULL, c->len + x->len);
        fxdpnt *quo = arb_expand(NULL, c->len + x->len);
	memset(sum->number, 0 , (c->len + x->len) * sizeof(ARBT));
	memset(quo->number, 0 , (c->len + x->len) * sizeof(ARBT));

        for(;i < 100;++i)
        {
                quo = arb_alg_d(x, c, quo, base, scale);
		//quo = ccarb_divide(x, c, quo, base, scale);
                sum = arb_add(quo, c, sum, base);
                c = arb_alg_d(sum, two, c, base, scale);
		//c = ccarb_divide(sum, two, c, base, scale);
                arb_print(c);
        }

        arb_free(sum);
        arb_free(quo);
        arb_free(two);

        return c;
}
