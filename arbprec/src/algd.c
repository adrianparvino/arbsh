#include <arbprec/arbprec.h>



fxdpnt *new_addition(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	fxdpnt *a_t = a;
	fxdpnt *b_t = b;
	int carry = 0;
	c = arb_expand(c, a->len + b->len);
	
	if (a->rp < b->rp)
	{
		a_t = b;
		b_t = a;
	}

	size_t diff = 0;
	size_t len = a_t->len;

	for (diff = 0;diff<= a_t->rp - b_t->rp;++diff, --len) 
		c->number[len] = a_t->number[len];
	
	if (a->lp < b->lp)
        {
                a_t = b;
                b_t = a;
        }
	c->len = a_t->len;
        c->rp = a_t->rp;
        c->lp = a_t->lp;
	
	// if diff changed then offset a_t
	//a_t += diff;
	// a_t should now be ready to go
	// long_add will need to be modified with the place() function and have both incrementors activated in order to do this in one operation
	// otherwise we may be able to reduce this to a long_add a short_add against the value of carry, if carry is present
	// so take the min length - the diff and pass everything to long_add. we'll end up with a partial answer
	//len = MIN(a_t->len , b_t->len);
	//carry = long_add(a_t->number , len, b_t->number, len, c->number  +diff, base);
	if (carry)
	{
		fprintf(stderr, "A carry is still present\n");
	}// else if a carry is not present, just perform a copy down int "c"
	
	// copy down the difference to the right of the radix into C

	// adjust radix offsets and pass the arguments as such to long_add

	// if a carry is left over, increment "c" and slam a "1" onto the end of it
	
	return c;
}

int long_sub(ARBT *u, size_t i, ARBT *v, size_t k, int b)
{ 
	int borrow = 0;
	int val = 0;
	for (; k+1 > 0; i--, k--) {
		val = u[i] - v[k] - borrow; 
		borrow = 0;
		if (val < 0) {
			val += b;
			borrow = 1;
		}
		u[i] = val;
	} 
	return borrow;
}

int long_add(ARBT *u, size_t i, ARBT *v, size_t k, ARBT *c, int b)
{
	int carry = 0;
	int val = 0;
	for (; k+1 > 0 ;i--, k--) {
		val = u[i] + v[k] + carry;
		carry = 0;
		//if (val > b-1) {
		if (val >= b) {
			val -= b;
			carry = 1;
		}
		//u[i] = val;
		c[i] = val;
		//c[i] = u[i];
	}
	return carry;
}

fxdpnt *arb_alg_d(fxdpnt *num, fxdpnt *den, fxdpnt *q, int b, int scale)
{ 
	ARBT *u;
	ARBT *v;
	ARBT *temp;
	ARBT qg = 0;
	ssize_t uscal = 0;
	int out_of_scale = 0;
	size_t quodig = 0;
	size_t offset = 0;
	size_t lea = 0;
	size_t leb = 0;
	size_t j = 0;

	lea = num->lp + den->rp;
	uscal = num->rp - den->rp;
	if (uscal < scale)
		offset = scale - uscal; 
	else
		offset = 0;

	u = arb_calloc(1, (num->lp + num->rp + offset + 3) * sizeof(ARBT));
	_arb_copy_core(u + 1, num->number, (num->lp + num->rp));

	leb = den->lp + den->rp;
	v = den->number;
	for (;*v == 0;v++,leb--); // this can run leb into the ground, be careful!!

	quodig = scale+1;
	out_of_scale = 0;
	if (leb > lea+scale) 
		out_of_scale = 1; 
	else
		if (!(leb>lea))
			quodig = lea-leb+scale+1;

	q = arb_expand(q, quodig+scale);
	q->lp = quodig-scale; q->rp = scale; q->len = q->lp + q->rp;
	
	temp = arb_malloc((leb+1) * sizeof(ARBT));

	if (out_of_scale)
		goto end;
	
	for (j=0, qg = b-1;j <= lea+scale-leb;++j, qg = b-1)
	{
		if (v[0] != u[j])
			qg = (u[j]*b + u[j+1]) / v[0];
		
		if (v[1]*qg > (u[j]*b + u[j+1] - v[0]*qg)*b + u[j+2])
		{
			qg = qg - 1;
			if (v[1]*qg > (u[j]*b + u[j+1] - v[0]*qg)*b + u[j+2])
				qg = qg - 1;
		} 
		// D4. [Multiply and Subtract]
		if (qg != 0){
			arb_mul_core(v, leb, &qg, 1, temp, b);
			if (!(long_sub(u+leb, j, temp, leb, b)))
				goto D7;
			qg = qg - 1;
			//if (long_add(u+leb, j, v, leb-1, b))
			if (long_add(u+leb, j, v, leb-1, u+leb, b))
				u[0] = 0; 
		}
		D7: // D7.
		q->number[j] = qg;
	}
	end:
	free(temp);
	free(u);
	return q;
}

