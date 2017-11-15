#include <arbprec.h>

fxdpnt *arb_divide2(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale)
{
	fxdpnt *qval;
	ARBT *num1;
	ARBT *num2;
	ARBT *mval;
	int scale1;
	int val;
	size_t qdigits = 0;
	size_t offset = 0;
	size_t lea = 0;
	size_t leb = 0;
	unsigned int qguess; // the idea that int is good val for holding carried ARBTs is ??
	unsigned int borrow;
	unsigned int carry;
	int out_of_scale;
	unsigned int normalize;
	size_t i = 0;
	size_t j = 0;
	size_t qdig = 0;

	lea = a->lp + b->rp;
	scale1 = a->rp - b->rp;

	if (scale1 < scale)
		offset = scale - scale1;
	else
		offset = 0;

	num1 = arb_malloc(a->lp + a->rp + offset + 2); // fix this +2
	memset(num1, 0, a->lp + a->rp + offset + 2);
	memcpy(num1 + 1, a->number, a->lp + a->rp);

	leb = b->lp + b->rp;
	num2 = arb_malloc(leb+1);
	memcpy(num2, b->number, leb);
	num2[leb] = 0;

	ARBT *freesave = num2;
	for (;*num2 == 0;num2++,leb--);

	qdigits = scale+1;
	out_of_scale = 0;
	if (leb > lea+scale) 
		out_of_scale = 1; 
	else
		if (!(leb>lea))
			qdigits = lea-leb+scale+1;

	qval = arb_new_num (qdigits-scale,scale);
	memset (qval->number, 0, qdigits);
	mval = arb_malloc (leb+1);

	if (out_of_scale)
		goto end;

	normalize = base / (num2[0] + 1);
	if (normalize != 1){
		arb_short_mul(num1, lea+scale1+offset+1, normalize, base);
		arb_short_mul(num2, leb, normalize, base);
	}

	qdig = 0;

	while (qdig <= lea+scale-leb)
	{ 
		if (*num2 == num1[qdig]) 
			qguess = base - 1;
		else 
			qguess = (num1[qdig]*base + num1[qdig+1]) / *num2;

		if (num2[1]*qguess > (num1[qdig]*base + num1[qdig+1] - *num2*qguess)*base + num1[qdig+2]) 
			qguess--;

		borrow = 0;
		if (qguess != 0){
			*mval = 0;
			short_mul2(num2, mval+1, leb, qguess, base); // +qdig is a new optimization -cmg

			for (i = qdig+leb, j = leb; j+1 > 0; i--, j--)
			{
				val = num1[i] - mval[j] - borrow; 
				borrow = 0;
				if (val < 0)
				{
					val += base;
					borrow = 1;
				}
				num1[i] = val;
			}

			if (borrow != 1)
				goto leave;

			qguess--;
			for (carry = 0, i = qdig+leb, j = leb-1; i > qdig ;i--, j--)
			{
				val = num1[i] + num2[j] + carry;
				carry = 0;
				if (val > base -1)
				{
					val -= base;
					carry = 1;
				}
				num1[i] = val;
			}
			if (carry == 1)
				num1[i] = (num1[i + 1]) % base;
		}
		leave:
		qval->number[qdig] = qguess;
		qdig++;
	}

	end: 
	arb_free_num (c); 
	free (mval);
	free (num1);
	free(freesave);
	return qval;
}
