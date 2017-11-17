#include <arbprec.h>
int arb_compare(fxdpnt *a, fxdpnt *b, int base)
{
        size_t i = 0;
        int sign = a->sign;

        if (a->sign == '-' && b->sign == '+')
                return -1; // smaller 
        if (a->sign == '+' && b->sign == '-')
                return 1;  // larger
        // else signs are the same, so move to subtraction steps
        fxdpnt *c = arb_expand(NULL, a->len + b->len); //FIXME initialize at runtime
        c = arb_sub(a, b, c, base);
        if (c->sign != sign){
                arb_free(c);
                return -1; // sign flipped so a < b  _smaller_
        }
        // check if c was all zeros indicating that a == b
        for (;i< c->len;++i){
                if (c->number[i] != 0){
                        arb_free(c);
                        return 1; // numbers were not equal so a > b (larger) 
                }
        }
        arb_free(c);
        return 0; // number were _equal_
}

