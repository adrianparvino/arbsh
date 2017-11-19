#include <arbprec/arbprec.h>

int long_sub(ARBT *u, size_t i, ARBT *temp, size_t k, int b)
{ 
	int borrow = 0;
	int val = 0;
	for (; k+1 > 0; i--, k--)
	{
		val = u[i] - temp[k] - borrow; 
		borrow = 0;
		if (val < 0)
		{
			val += b;
			borrow = 1;
		}
		u[i] = val;
	} 
	return borrow;
}

int long_add(ARBT *u, size_t i, ARBT *v, size_t k, int b)
{
	int carry = 0;
	int val = 0;
	for (carry = 0 ; k+1 > 0 ;i--, k--)
	{
		val = u[i] + v[k] + carry;
		carry = 0;
		if (val > b-1)
		{
			val -= b;
			carry = 1;
		}
		u[i] = val;
	}
	return carry;
}

fxdpnt *arb_alg_d(fxdpnt *num, fxdpnt *den, fxdpnt *c, int b, int scale)
{
	fxdpnt *q;
	ARBT *u;
	ARBT *v;
	ARBT *temp;

	//int uscal = 0;
	ssize_t uscal = 0;//FIXME: figure out how to use a size_t for this
	int val = 0;//TODO: research what this maximum value could be and devise a safety mech
	int qg = 0;// never more than base 
	int borrow = 0; // never more than 1
	int carry = 0; // never more than 1
	int out_of_scale = 0; // a bool
	int d = 0; // TODO: research the maximum value of the normalization relative to the base "b"
	size_t quodig = 0;
	size_t offset = 0;
	size_t lea = 0;
	size_t leb = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;

	lea = num->lp + den->rp;
	uscal = num->rp - den->rp;

	if (uscal < scale)
		offset = scale - uscal;
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

	q = arb_new_num(quodig-scale,scale);// FIXME replace this with an expansion of "c"
	memset(q->number, 0, quodig * sizeof(ARBT));
	temp = arb_malloc((leb+1) * sizeof(ARBT));

	if (out_of_scale)
		goto end;

	// D1. [Normalize]
	// Set D <-- [B/(V1 + 1)]
	d = b / (v[0] + 1);
	// if D == 1 set U0 <-- 0 `this was set to zero at "ref 1" above`
	if (d != 1){
		// Set (U1U2...Um+n)B * D 
		arb_short_mul(u, lea+uscal+offset+1, d, b);
		// Set (V1V2...Vm+n)B * D
		arb_short_mul(v, leb, d, b);
		// "Note the introduction of a new digit U0 at the left of U1"
	}
	// D2. [Initialize J]
	// Set J <-- 0
	j = 0;
	// The loop on J. (UjUj+1...Uj+n)B / (VjVj+1...Vj+n)B to get a single digit of Qj
	while (j <= lea+scale-leb)
	{
		// D3. [Calculate qg]
		// if Uj == Vj, set qg <-- B-1
		if (v[0] == u[j])
			qg = b - 1;
		// otherwise set qg <-- [(UjB+U(j+1))/V1]
		else	qg = (u[j]*b + u[j+1]) / v[0];
		// Now test if V2qg > (UjB + U(j+1) - qgV1)B + U(j+2) if so decrease qg by 1
		if (v[1]*qg > (u[j]*b + u[j+1] - v[0]*qg)*b + u[j+2])
		{ 
			qg = qg - 1;// "and repeat the test"
			if (v[1]*qg > (u[j]*b + u[j+1] - v[0]*qg)*b + u[j+2])
				qg = qg - 1;
		}
		
		// D4. [Multiply and Subtract]
		if (qg != 0){
			// "Replace (UjU(j+1)...U(j+n))B by (UjUj+1...Uj+n)B - qg times (V1V2...Vn)"
			temp[0] = 0;
			// `obtain` qg times (V1V2...Vn) `and put into temp`
			short_mul2(v, temp+1, leb, qg, b);
			//  (UjUj+1...Uj+n)B - qgtimes (V1V2...Vn)
			borrow = long_sub(u, j+leb, temp, leb, b);
			// D5. [Test Remainder] Set Qj <-- qg.
			// if D4 was negative go to D6, otherwise go on to D7
			if (borrow != 1)
				goto D7;
			// D6. [Add back.]
			// Decrease Qj by 1
			qg = qg - 1;
			// Add (0V1V2...Vn) to (UjU(j+1)U(j+2)...U(j+n))b
			carry = long_add(u, leb+j, v, leb-1, b);
			// "A carry will occur to the left of Uj and it should be ignored since it
			// cancels with the borrow that occured in D4" `zero it out`
			if (carry == 1) 
				u[i] = 0;//TODO: research this more carefully
				//u[i] = (u[i + 1]) % b; 
		}
		D7: // D7. [Loop on j] `and handle remnants of step D5`
		// Increase J by one. now if j >= m go back to D3
		q->number[j] = qg;
		j++;
	}
	// D8. [Unnormalize]
	// (Q0Q1...Qm)b is the desired quotient, `but` the remainder is ((U(m+1)...U(m+n))b / d)
	// TODO: write a "short division" function to accomplish this and figure and devise a
	// method to make this function do either job. this will probably require another function
	// argument
	end: 
	arb_free_num(c); 
	free(temp);
	free(u);
	free(freesave);
	return q;
}

