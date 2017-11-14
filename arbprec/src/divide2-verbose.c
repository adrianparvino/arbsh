#include <arbprec.h>


fxdpnt *arb_divide2_verbose(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale)
{
	fxdpnt *qval;
	unsigned char *num1, *num2;
	unsigned char *qptr;
	int scale1;
	int val;
	//unsigned int lea, leb, qdigits, offset;
	unsigned int qdigits, offset;
	size_t lea = 0;
	size_t leb = 0;
	//unsigned int qdig, qguess, borrow, carry;
	unsigned int qguess, borrow, carry;
	unsigned char *mval;
	int out_of_scale;
	unsigned int normalize;
	size_t i, j;
	size_t qdig = 0;
	/* these variables are simply to help deduce the big O properties of the equation */
	size_t iterations = 0;
	size_t subs = 0;
	size_t adds = 0;
	size_t hqguess = 0;
	size_t lqguess = 0;
	size_t baseg = 0;
	size_t nonbaseg = 0;

	lea = a->lp + b->rp;
	scale1 = a->rp - b->rp;

	if (scale1 < scale)
		offset = scale - scale1;
	else
		offset = 0;

	num1 = arb_malloc(a->lp+a->rp+offset+2); // fix this +2
	memset (num1, 0, a->lp+a->rp+offset+2);
	memcpy (num1+1, a->number, a->lp+a->rp);

	leb = b->lp + b->rp;
	num2 = arb_malloc (leb+1);
	memcpy (num2, b->number, leb);
	num2[leb] = 0;

	unsigned char *freesave = num2;
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

	normalize = base / ((int)*num2 + 1);
	if (normalize != 1){
		arb_short_mul(num1, lea+scale1+offset+1, normalize, base);
		arb_short_mul(num2, leb, normalize, base);
	}

	qdig = 0;
	if (leb > lea)
		qptr = (unsigned char *) qval->number+leb-lea;
	else
		qptr = (unsigned char *) qval->number;

	while (qdig <= lea+scale-leb)
	{ 
		if (*num2 == num1[qdig]) 
			qguess = base -1;
		else 
			qguess = (num1[qdig]*base + num1[qdig+1]) / *num2;

		borrow = 0;
		if (qguess != 0){
			*mval = 0;
			short_mul2(num2, mval+1, leb, qguess, base);

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
				++subs;
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
		fprintf(stderr, "%zu baseg\n", baseg);
		fprintf(stderr, "%zu nonbaseg\n", nonbaseg);
	}
	end: 
	arb_free_num (c); 
	free (mval);
	free (num1);
	free(freesave);
	return qval;
}
