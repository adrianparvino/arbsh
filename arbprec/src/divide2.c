#include <arbprec.h>



fxdpnt *arb_divide2(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale)
{
        fxdpnt *qval;
        unsigned char *num1, *num2;
        unsigned char *qptr;
        int scale1;
        int val;
        unsigned int lea, leb, qdigits, offset;
        unsigned int qdig, qguess, borrow, carry;
        unsigned char *mval;
        int out_of_scale;
        unsigned int normalize;
        size_t i, j, l;
        /* these variables are simply to help deduce the big O properties of the equation */
        size_t iterations = 0;
        size_t subs = 0;
        size_t adds = 0;
        size_t hqguess = 0;
        size_t lqguess = 0;

        lea = a->lp + b->rp;
        scale1 = a->rp - b->rp;
        
        if (scale1 < scale)
                offset = scale - scale1;
        else
                offset = 0;
        num1 = arb_malloc(a->lp+a->rp+offset+2);
        memset (num1, 0, a->lp+a->rp+offset+2);
        memcpy (num1+1, a->number, a->lp+a->rp);

        leb = b->lp + b->rp;
        num2 = arb_malloc (leb+1);
        memcpy (num2, b->number, leb);
        *(num2+leb) = 0;

        unsigned char *freesave = num2;
        for (;*num2 == 0;num2++,leb--);

        if (leb > lea+scale)
        {
                qdigits = scale+1;
                out_of_scale = 1;
        }
        else
        {
                out_of_scale = 0;
                if (leb>lea)
                        qdigits = scale+1;
                else
                        qdigits = lea-leb+scale+1;
        }
        qval = arb_new_num (qdigits-scale,scale);
        memset (qval->number, 0, qdigits);
        mval = arb_malloc (leb+1);

        if (out_of_scale)
                goto end;

        normalize = base / ((int)*num2 + 1);
        if (normalize != 1){
                short_multiply(num1, lea+scale1+offset+1, normalize, num1, base);
                short_multiply(num2, leb, normalize, num2, base);
        }

        qdig = 0;
        if (leb > lea)
                qptr = (unsigned char *) qval->number+leb-lea;
        else
                qptr = (unsigned char *) qval->number;

        while (qdig <= lea+scale-leb)
        {

                if (*num2 == num1[qdig])
		{
			//fprintf(stderr, "how often does this happen\n");
                        qguess = base -1;
		}
                else
		{
			//fprintf(stderr, "as opposed to this\n");
                        qguess = (num1[qdig]*base + num1[qdig+1]) / *num2;
		}

                borrow = 0;
                if (qguess != 0){
                        *mval = 0;
                        short_multiply(num2, leb, qguess, mval+1, base);
                        for (i = qdig+leb, j = leb, l = 0; l < leb+1; l++, i--, j--)
                        {
                                val = num1[i] - mval[j] - borrow;
				borrow = 0;
                                if (val < 0)
                                {
                                        val += base;
                                        borrow = 1;
                                }
                                        
                                num1[i] = val;
                                ++subs;
                        }
                

                	if (borrow != 1)
				goto leave;
                
                        qguess--;
                        for (carry = 0, i = qdig+leb, j = leb-1, l = 0; l < leb; l++, i--, j--)
                        {
                                val = num1[i] + num2[j] + carry;
				carry = 0;
                                if (val > base -1)
                                {
                                        val -= base;
                                        carry = 1;
                                }
                                num1[i] = val;
                                ++adds;
                        }
                        if (carry == 1)
                                num1[i] = (num1[i + 1]) % base;
			
                
		}
		leave:
                ++iterations;
                *qptr++ = qguess;
                qdig++;
        }

        if (verbosity)
        {
                fprintf(stderr, "%zu iterations\n", iterations);
                fprintf(stderr, "%zu adds\n", adds);
                fprintf(stderr, "%zu subs\n", subs);
                fprintf(stderr, "%zu hqguess\n", hqguess);
                fprintf(stderr, "%zu lqguess\n", lqguess);
        }
        end: 
        arb_free_num (c); 
        free (mval);
        free (num1);
        free(freesave);
        return qval;
}
