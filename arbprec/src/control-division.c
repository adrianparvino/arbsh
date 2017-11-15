#include <arbprec.h>

fxdpnt *arb_divide(fxdpnt *n1, fxdpnt *n2, fxdpnt *quot, int base, int scale)
{
	fxdpnt *qval;
	unsigned char *num1, *num2;
	unsigned char *n2ptr, *qptr;
	int scale1;
	int val;
	unsigned int len1, len2, scale2, qdigits, extra, count;
	unsigned int qdig, qguess, borrow, carry;
	unsigned char *mval;
	char zero;
	unsigned int norm;
	size_t i, j;
	/* these three variables are simply to help deduce the big O properties of the equation */
	size_t iterations = 0;
	size_t subs = 0;
	size_t adds = 0;
	size_t hqguess = 0;
	size_t lqguess = 0;
	size_t baseg = 0;
        size_t nonbaseg = 0;

	/* Set up the divide.	Move the decimal point on n1 by n2's scale.
	 Remember, zeros on the end of num2 are wasted effort for dividing. */
	// removing zeros of a number essentially performs a logical/bitwise shift
	// in base 10 it would make 00990 into 00099. making this an argument reduction
	// routine. in my opinion this may lead to too much cognitive overhead --cmg

	scale2 = n2->rp;
	n2ptr = (unsigned char *) n2->number+n2->lp+scale2-1; // this -1 seems odd but i have seen it before
	while ((scale2 > 0) && (*n2ptr-- == 0))
		scale2--;

	// here we see the effects of the logical shift again
	len1 = n1->lp + scale2;
	scale1 = n1->rp - scale2;

	//this may also be the effect of the logical shift
	if (scale1 < scale)
		extra = scale - scale1;
	else
		extra = 0;
	num1 = arb_malloc(n1->lp+n1->rp+extra+2);
	memset (num1, 0, n1->lp+n1->rp+extra+2);
	memcpy (num1+1, n1->number, n1->lp+n1->rp);

	// here the effects of the logical shift must again be reapplied
	len2 = n2->lp + scale2;
	// and by now we are done with the logical shifting mechanism
	num2 = arb_malloc (len2+1);
	memcpy (num2, n2->number, len2);
	*(num2+len2) = 0;
	n2ptr = num2;

	while (*n2ptr == 0)
	{
		n2ptr++;
		len2--;
	}

	/* Calculate the number of quotient digits. */
	// this basically turns everything into 0000..s if the answer can't be found
	if (len2 > len1+scale)
	{
		qdigits = scale+1;
		zero = 1;
	}
	else
	{
		zero = 0;
		if (len2>len1)
		{
			qdigits = scale+1;	/* One for the zero integer part. */
			
		}
		else
		{
			qdigits = len1-len2+scale+1;
		
		}
	}

	/* Allocate and zero the storage for the quotient. */
	qval = arb_new_num (qdigits-scale,scale);
	
	memset (qval->number, 0, qdigits);

	/* Allocate storage for the temporary storage mval. */
	mval = arb_malloc (len2+1);

	/* Now for the full divide algorithm. */
	if (zero)
		goto end;
	
	/* Normalize */
	norm =	base / ((int)*n2ptr + 1);
	
	/* bases under 10 have a normalization factor of < 2 -cmg */
	if (norm != 1){ 
		short_multiply (num1, len1+scale1+extra+1, norm, num1, base);
		short_multiply (n2ptr, len2, norm, n2ptr, base);
	}

	/* Initialize divide loop. */
	qdig = 0;
	// this section simply leaves 0000s that will end up on the left of the answer
	if (len2 > len1)
		qptr = (unsigned char *) qval->number+len2-len1; 
	else
		qptr = (unsigned char *) qval->number;

	
	while (qdig <= len1+scale-len2)
	{
		/* Calculate the quotient digit guess. */
		if (*n2ptr == num1[qdig])
		{
			qguess = base -1;
			++baseg;
		}
		else{
			qguess = (num1[qdig]*base + num1[qdig+1]) / *n2ptr;
			++nonbaseg;
		}

		/* Test qguess -- twice */
	
		if (n2ptr[1]*qguess > (num1[qdig]*base + num1[qdig+1] - *n2ptr*qguess)*base + num1[qdig+2])
		{ 
			++hqguess;
			qguess--;
			if (n2ptr[1]*qguess > (num1[qdig]*base + num1[qdig+1] - *n2ptr*qguess)*base + num1[qdig+2])
			{ 
				++lqguess;
				qguess--; 
			}
		}
	
		/* Multiply and subtract. */
		borrow = 0;
		if (qguess != 0){
		// this loop appears to always happen
			
			*mval = 0;
			short_multiply (n2ptr, len2, qguess, mval+1, base);
			for (i = qdig+len2, j = len2, count = 0; count < len2+1; count++, i--, j--)
			{ 
				val = num1[i] - mval[j] - borrow;
				if (val < 0)
				{
					val += base;
					borrow = 1;
				}
				else
					borrow = 0;
				num1[i] = val;
				++subs;
			}	
		}

		/* Test for negative result. */
		if (borrow == 1)
		{
			qguess--;
			for (carry = 0, i = qdig+len2, j = len2-1, count = 0; count < len2; count++, i--, j--)
			{ 
				val = num1[i] + n2ptr[j] + carry;
				if (val > base -1)
				{
					val -= base;
					carry = 1;
				}
				else
					carry = 0;
				num1[i] = val;
				++adds;
			}
			if (carry == 1)
				num1[i] = (num1[i + 1]) % base;
		}
		++iterations;
		/* We now know the quotient digit. */
		// there is exactly one outer iteration per true scale length
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
		fprintf(stderr, "%d scale2\n", scale2);
		fprintf(stderr, "%zu baseg\n", baseg);
                fprintf(stderr, "%zu nonbaseg\n", nonbaseg);
	}
	end:
	/* Clean up and return the number. */
	qval->sign = ( n1->sign == n2->sign ? '+' : '-' );
	
	arb_free_num (quot);

	/* Clean up temporary storage. */
	free (mval);
	free (num1);
	free (num2);
	return qval;
}

