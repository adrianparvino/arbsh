#include <arbprec.h>
fxdpnt *toym_babylonian_sqrt(fxdpnt *x, fxdpnt *c, int base)
{
        // This function is provided to test the effectiveness of the division
        // and subtraction routines. It is not intended to be a performant sqrt
        size_t i = 0;
        toym_init(c);
        c = toym_expand(c, c->len + x->len);
        toym_copyarr(c->number, x->number, x->len);
        c->len = x->len;
        fxdpnt *two = toym_str2fxdpnt("2");
        fxdpnt *sum = toym_expand(NULL, c->len + x->len);
        fxdpnt *quo = toym_expand(NULL, c->len + x->len);

        for(;i < 40;++i)
        {
                quo = toym_div(x, c, quo, base);
                sum = toym_add(quo, c, sum, base);
                c = toym_div(sum, two, c, base);
                //toym_print(c);
        }

        toym_free(sum);
        toym_free(quo);
        toym_free(two);

        return c;
}
