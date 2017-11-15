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

	scale2 = n2->rp;
	n2ptr = (unsigned char *) n2->number+n2->lp+scale2-1; 
	while ((scale2 > 0) && (*n2ptr-- == 0))
		scale2--; 

	len1 = n1->lp + scale2;
	scale1 = n1->rp - scale2; 

	if (scale1 < scale)
		extra = scale - scale1;
	else
		extra = 0;
	num1 = arb_malloc(n1->lp+n1->rp+extra+2);
	memset (num1, 0, n1->lp+n1->rp+extra+2);
	memcpy (num1+1, n1->number, n1->lp+n1->rp); 

	len2 = n2->lp + scale2; 
	num2 = arb_malloc (len2+1);
	memcpy (num2, n2->number, len2);
	*(num2+len2) = 0;
	n2ptr = num2;

	while (*n2ptr == 0)
	{
		n2ptr++;
		len2--;
	} 

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
			qdigits = scale+1;
			
		}
		else
		{
			qdigits = len1-len2+scale+1;
		
		}
	} 
	qval = arb_new_num (qdigits-scale,scale); 
	memset (qval->number, 0, qdigits); 
	mval = arb_malloc (len2+1); 
	if (zero)
		goto end; 

	norm =	base / ((int)*n2ptr + 1); 
	if (norm != 1){ 
		short_multiply (num1, len1+scale1+extra+1, norm, num1, base);
		short_multiply (n2ptr, len2, norm, n2ptr, base);
	}


	qdig = 0;

	if (len2 > len1)
		qptr = (unsigned char *) qval->number+len2-len1; 
	else
		qptr = (unsigned char *) qval->number; 
	
	while (qdig <= len1+scale-len2)
	{ 
		if (*n2ptr == num1[qdig])
		{
			qguess = base -1; 
		}
		else{
			qguess = (num1[qdig]*base + num1[qdig+1]) / *n2ptr; 
		} 
	
		if (n2ptr[1]*qguess > (num1[qdig]*base + num1[qdig+1] - *n2ptr*qguess)*base + num1[qdig+2])
		{ 
			--qguess;
			if (n2ptr[1]*qguess > (num1[qdig]*base + num1[qdig+1] - *n2ptr*qguess)*base + num1[qdig+2])
			{ 
				--qguess;
			}
		} 

		borrow = 0;
		if (qguess != 0){ 
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
	
			}	
		}
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

			}
			if (carry == 1)
				num1[i] = (num1[i + 1]) % base;
		}

		*qptr++ = qguess;
		qdig++;
	} 

	end: 
	qval->sign = ( n1->sign == n2->sign ? '+' : '-' ); 
	arb_free_num (quot); 
	free (mval);
	free (num1);
	free (num2);
	return qval;
}

#include <arbprec.h>

void short_multiply(unsigned char *num, int size, int digit, unsigned char *result, int base)
{
	int carry, value;
	size_t i = 0;

	if (digit == 0)
		memset (result, 0, size);
	else if (digit == 1)
		memcpy (result, num, size);
	else
	{
		for (carry = 0, i = size ; i>0;i--)
		{
			value = num[i-1] * digit + carry;
			result[i-1] = value % base;
			carry = value / base;

		}
		if (carry != 0)
			result[i-1] = carry;
	}
}

