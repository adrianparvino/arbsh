#include <arbprec.h>

fxdpnt *arb_alg_d(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale)
{
	
	/*
		terms:
			U   numerator
			V   denominator
			D   normalization multiplicand
			B/b base
			J/j loop counter
			Qj  quotient or answer
			q'  quotient guess
			^() superscript (possibly raised to power of)
			""  "Knuth's descriptions"
			``  `my own descriptions`

			
	*/
	
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
	unsigned int qguess; 
	unsigned int borrow;
	unsigned int carry;
	int out_of_scale;
	unsigned int normalize;
	size_t i = 0;
	//size_t j = 0; // j is reserved for knuthian terms
	size_t k = 0;

	size_t qdig = 0;

	lea = a->lp + b->rp;
	scale1 = a->rp - b->rp;

	if (scale1 < scale)
		offset = scale - scale1;
	else
		offset = 0;

	num1 = arb_malloc((a->lp + a->rp + offset + 2) * sizeof(ARBT));
	memset(num1, 0, (a->lp + a->rp + offset + 2) * sizeof(ARBT)); // ref 1
	memcpy(num1 + 1, a->number, (a->lp + a->rp) * sizeof(ARBT));

	leb = b->lp + b->rp;
	num2 = arb_malloc((leb+1) * sizeof(ARBT));
	memcpy(num2, b->number, leb * sizeof(ARBT));
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
	memset (qval->number, 0, qdigits * sizeof(ARBT));
	mval = arb_malloc ((leb+1) * sizeof(ARBT));

	if (out_of_scale)
		goto end;

	// D1. [Normalize]
	// Set D <-- [B/(V1 + 1)]
	normalize = base / (num2[0] + 1);
	// if D == 1 set U0 <-- 0 (this was set to zero at "ref 1" above)
	if (normalize != 1){
		// Set (U1U2...Um+n)B * D 
		arb_short_mul(num1, lea+scale1+offset+1, normalize, base);
		// Set (V1V2...Vm+n)B * D
		arb_short_mul(num2, leb, normalize, base);
		// Note the introduction of a new digit U0 at the left of U1
	}
	// D2. [Initialize J]
	// Set J <-- 0
	qdig = 0;
	// The loop on J. (UjUj+1...Uj+n)B / (VjVj+1...Vj+n)B to get a single digit of Qj
	while (qdig <= lea+scale-leb)
	{
		// D3. [Calculate q']
		// if Uj == Vj, set q' <-- B-1
		if (*num2 == num1[qdig]) 
			qguess = base - 1;
		// otherwise set q' <-- [(UjB+U(j+1))/V1]
		else	qguess = (num1[qdig]*base + num1[qdig+1]) / *num2;
		// Now test if V2q' > (UjB + U(j+1) - q'V1)B + U(j+2)
		if (num2[1]*qguess > (num1[qdig]*base + num1[qdig+1] - *num2*qguess)*base + num1[qdig+2])
		// if so decrease q' by 1 and repeat the test -- NOTE: THIS NEEDS TO BE ADDED BACK
			qguess--;
		
		// D4. [Multiply and Subtract]
		borrow = 0;
		if (qguess != 0){
			// "Replace (UjUj+1...Uj+n)B by (UjUj+1...Uj+n)B - q'times (V1V2...Vn)"
			// "The digits (UjUj+1...Uj+n) should be kept positive" `so use a temp val`
			// "if the result of this step was negative (UjUj+1...Uj+n)B is actually negative"
			//  "(UjUj+1...Uj+n)B should be left as the true value plus B^(n+1) as the B's "
			// "complement of the true value, and a "borrow" to the left should be remembered"
			*mval = 0;
			// `obtain` q'times (V1V2...Vn) `and put into mval`
			short_mul2(num2, mval+1, leb, qguess, base);
			//  (UjUj+1...Uj+n)B - q'times (V1V2...Vn)
			for (i = qdig+leb, k = leb; k+1 > 0; i--, k--)
			{
				val = num1[i] - mval[k] - borrow; 
				borrow = 0;
				if (val < 0)
				{
					val += base;
					borrow = 1;
				}
				num1[i] = val;
			}
			// D5. [Test Remainder] Set Qj <-- q'. `this step appears to be misordered`
			// If the result of of D4 was negative go to D6, otherwise go on to D7
			if (borrow != 1)
				goto leave;
			// D6. [Add back.]
			// Decrease Qj by 1
			qguess--;
			// Add (0V1V2...Vn) to (UjU(j+1)U(j+2)...U(j+n))b
			for (carry = 0, i = qdig+leb, k = leb-1; i > qdig ;i--, k--)
			{
				val = num1[i] + num2[k] + carry;
				carry = 0;
				if (val > base -1)
				{
					val -= base;
					carry = 1;
				}
				num1[i] = val;
			}
			// A carry will occur to the left of Uj and it should be ignored since it
			// cancels wth the borrow that occured in D4
			if (carry == 1)
				// `i is 0 here so it should be "canceled', possible bug -- 
				// zeroing appears to do the same thing
				num1[i] = (num1[i + 1]) % base; 
		}
		leave:
		// `this appears to be a remnant of step D5`
		qval->number[qdig] = qguess;
		// D7. [Loop on j]
		// Increase J by one. now if j >= m go back to D3
		qdig++;
	}

	end: 
	arb_free_num(c); 
	free(mval);
	free(num1);
	free(freesave);
	return qval;
}
