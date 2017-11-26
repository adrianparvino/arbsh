#include <arbprec/arbprec.h>


//carry = long_add(a->number, a->len - adiff, b->number, b->len - bdiff, c->number, base);
fxdpnt *new_addition(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	int carry = 0;
	c = arb_expand(c, a->len + b->len);
	//c->len = a->len + b->len;
	
	size_t adiff = 0;
	size_t bdiff = 0;
	size_t len = 0;
	size_t a_extra = 0;
	size_t b_extra = 0;
	size_t extra = 0;
	size_t rclen = 0;

	c->len = MAX(a->len, b->len);
	c->rp = MAX(a->rp, b->rp);
	c->lp = MAX(a->lp, b->lp);
	rclen = c->len - 1;
	
	if (a->rp > b->rp)
	{ 
		len = a->len -1;
		for (adiff = 0;adiff< a->rp - b->rp;++adiff, --len, --rclen) 
			c->number[rclen] = a->number[len];
		
	}else if (a->rp < b->rp)
	{
		len = b->len -1;
		for (bdiff = 0;bdiff< b->rp - a->rp;++bdiff, --len) 
			c->number[len] = b->number[len];
	}
	size_t min = MIN(b->len, a->len); // good !! 
	//carry = long_add(a->number, min, b->number, min, c->number, base); 
	size_t differ = MAX(adiff, bdiff);

	size_t minlp = MIN(a->lp, b->lp);
	size_t minrp = MIN(a->rp, b->rp);
	size_t maxlp = MAX(a->lp, b->lp);
	size_t real = minlp + minrp;

	printf("%zu real\n", real);

	if (a->lp > b->lp)
	{
		extra = a->lp - b->lp;
		carry = long_add(a->number + extra, real + extra, b->number, real, c->number, rclen, real, base);

	}else if (b->lp > a->lp)
	{
		extra = b->lp - b->rp;
		//carry = long_add(a->number, real , b->number + extra, real +extra, c->number, real,  base);
	}else{
		//carry = long_add(a->number, min, b->number, min , c->number, min, base);
	}

	if (carry)
	{
		fprintf(stderr, "A carry is still present\n");
		arb_print(c);
		printf("====\n");
		//c->number[0] = 1;
	}
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

int long_add(ARBT *u, size_t i, ARBT *v, size_t k, ARBT *c, size_t ci, size_t real, int b)
{
	int carry = 0;
	int val = 0;
	for (; k + 1 > 0 ;i--, k--, real--, ci--) {
		val = u[i] + v[k] + carry;
		carry = 0;
		if (val >= b) {
			val -= b;
			carry = 1;
		}
		c[ci] = val;
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

	j = 0;
	if (leb >lea)
		j = leb -lea;
		////q->number+=leb-lea;
	
	for ( qg = b-1;j <= lea+scale-leb;++j, qg = b-1)
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
			if (long_add(u+leb, j, v, leb-1, u+leb, j, leb-1, b))
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

