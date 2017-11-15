#include <arbprec.h>

fxdpnt *arb_alg_d(fxdpnt *num, fxdpnt *den, fxdpnt *c, int b, int scale)
{
	
	/*
		Explanation of terms in comments:
			U   numerator
			V   denominator
			D   normalization multiplicand
			B/b b
			J/j loop counter
			Qj  quotient or answer
			qg  quotient guess
			^() superscript (possibly raised to power of)
			""  "Knuth's descriptions"
			``  `my own descriptions`
		The actual code reflects these variables names to some extent.
		However, because array subscripting did not have to be implied
		in the code I was able to more closely mirror the actual 
		variable names that Knuth used in the informative text.
			
	*/
	
	fxdpnt *q;
	ARBT *u;
	ARBT *v;
	ARBT *mval;
	int scale1;
	int val;
	size_t quodig = 0;
	size_t offset = 0;
	size_t lea = 0;
	size_t leb = 0;
	unsigned int qg; 
	unsigned int borrow;
	unsigned int carry;
	int out_of_scale;
	unsigned int d;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;

	lea = num->lp + den->rp;
	scale1 = num->rp - den->rp;

	if (scale1 < scale)
		offset = scale - scale1;
	else
		offset = 0;

	u = arb_malloc((num->lp + num->rp + offset + 2) * sizeof(ARBT));
	memset(u, 0, (num->lp + num->rp + offset + 2) * sizeof(ARBT)); // ref 1
	memcpy(u + 1, num->number, (num->lp + num->rp) * sizeof(ARBT));

	leb = den->lp + den->rp;
	v = arb_malloc((leb+1) * sizeof(ARBT));
	memcpy(v, den->number, leb * sizeof(ARBT));
	v[leb] = 0;

	ARBT *freesave = v;
	for (;*v == 0;v++,leb--);

	quodig = scale+1;
	out_of_scale = 0;
	if (leb > lea+scale) 
		out_of_scale = 1; 
	else
		if (!(leb>lea))
			quodig = lea-leb+scale+1;

	q = arb_new_num(quodig-scale,scale);
	memset(q->number, 0, quodig * sizeof(ARBT));
	mval = arb_malloc((leb+1) * sizeof(ARBT));

	if (out_of_scale)
		goto end;

	// D1. [Normalize]
	// Set D <-- [B/(V1 + 1)]
	d = b / (v[0] + 1);
	// if D == 1 set U0 <-- 0 `this was set to zero at "ref 1" above`
	if (d != 1){
		// Set (U1U2...Um+n)B * D 
		arb_short_mul(u, lea+scale1+offset+1, d, b);
		// Set (V1V2...Vm+n)B * D
		arb_short_mul(v, leb, d, b);
		// Note the introduction of a new digit U0 at the left of U1
	}
	// D2. [Initialize J]
	// Set J <-- 0
	j = 0;
	// The loop on J. (UjUj+1...Uj+n)B / (VjVj+1...Vj+n)B to get a single digit of Qj
	while (j <= lea+scale-leb)
	{
		// D3. [Calculate qg]
		// if Uj == Vj, set qg <-- B-1
		if (*v == u[j]) 
			qg = b - 1;
		// otherwise set qg <-- [(UjB+U(j+1))/V1]
		else	qg = (u[j]*b + u[j+1]) / *v; // FIXME: use v[0]
		// Now test if V2qg > (UjB + U(j+1) - qgV1)B + U(j+2) if so decrease qg by 1
		if (v[1]*qg > (u[j]*b + u[j+1] - *v*qg)*b + u[j+2]) // FIXME: use v[0]
		{ 
			qg = qg - 1;;// "and repeat the test"
			if (v[1]*qg > (u[j]*b + u[j+1] - *v*qg)*b + u[j+2]) // FIXME: use v[0]
				qg = qg - 1;
		}
		
		// D4. [Multiply and Subtract]
		borrow = 0;
		if (qg != 0){
			// "Replace (UjU(j+1)...U(j+n))B by (UjUj+1...Uj+n)B - qgtimes (V1V2...Vn)"
			*mval = 0;
			// `obtain` qgtimes (V1V2...Vn) `and put into mval`
			short_mul2(v, mval+1, leb, qg, b);
			//  (UjUj+1...Uj+n)B - qgtimes (V1V2...Vn)
			for (i = j+leb, k = leb; k+1 > 0; i--, k--)
			{
				val = u[i] - mval[k] - borrow; 
				borrow = 0;
				if (val < 0)
				{
					val += b;
					borrow = 1;
				}
				u[i] = val;
			} 
			// D5. [Test Remainder] Set Qj <-- qg.
			// if D4 was negative go to D6, otherwise go on to D7
			if (borrow != 1)
				goto D7;
			// D6. [Add back.]
			// Decrease Qj by 1
			qg = qg - 1;
			// Add (0V1V2...Vn) to (UjU(j+1)U(j+2)...U(j+n))b
			for (carry = 0, i = j+leb, k = leb-1; i > j ;i--, k--)
			{
				val = u[i] + v[k] + carry;
				carry = 0;
				if (val > b -1)
				{
					val -= b;
					carry = 1;
				}
				u[i] = val;
			}
			// "A carry will occur to the left of Uj and it should be ignored since it
			// cancels wth the borrow that occured in D4" `zero it out`
			if (carry == 1) 
				u[i] = (u[i + 1]) % b; 
		}
		D7: // D7. [Loop on j] `and handle remnants of step D5`
		// Increase J by one. now if j >= m go back to D3
		q->number[j] = qg;
		j++;
	}

	end: 
	arb_free_num(c); 
	free(mval);
	free(u);
	free(freesave);
	return q;
}
