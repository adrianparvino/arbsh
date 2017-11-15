#include <arbprec.h>

fxdpnt *arb_mul(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
        int i = 0, j = 0, sum = 0, carry = 0;
        size_t k = 0;
        //arb_setsign(a, b, c);
        c = arb_expand(c, a->len + b->len);
        memset(c->number, 0, (a->len + b->len) * sizeof(ARBT));

        for ( i = a->len - 1; i >= 0 ; i--){
                for ( j = b->len - 1, k = i + j + 1, carry = 0; j >= 0 ; j--, k--){
                        sum = (a->number[i]) * (b->number[j]) + (c->number[k]) + carry;
                        carry = sum / base;
                        c->number[k] = (sum % base);
                }
                c->number[k] += carry;
        }
        c->len = a->len + b->len;
        c->lp = a->lp + b->lp;
        return c;
}

