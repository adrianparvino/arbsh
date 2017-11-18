#include <arbprec/arbprec.h>
fxdpnt *arb_babylonian_sqrt(fxdpnt *x, fxdpnt *c, int base, int scale)
{
        // This function is provided to test the effectiveness of the division
        // and subtraction routines. It is not intended to be a performant sqrt
        size_t i = 0;
        arb_init(c);
        c = arb_expand(c, c->len + x->len);
        memcpy(c->number, x->number, x->len * sizeof(ARBT));
        c->len = x->len;
        fxdpnt *two = arb_str2fxdpnt("2");
        fxdpnt *sum = arb_expand(NULL, c->len + x->len);
        fxdpnt *quo = arb_expand(NULL, c->len + x->len);

        for(;i < 40;++i)
        {
                quo = arb_division(x, c, quo, base, scale);
                sum = arb_add(quo, c, sum, base);
                c = arb_division(sum, two, c, base, scale);
                //arb_print(c);
        }

        arb_free(sum);
        arb_free(quo);
        arb_free(two);

        return c;
}
