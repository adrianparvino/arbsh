#include <arbprec.h>

void arb_free(fxdpnt *flt)
{
        if (flt->number)
                free(flt->number);
        free(flt);
}

void arb_printold(fxdpnt *flt)
{
        size_t i = 0;

        if (flt->sign == '-')
                putchar(flt->sign);
        for (i = 0; i < flt->len ; ++i){
                if (flt->lp == i)
                        putchar('.');
                putchar(arb_highbase((flt->number[i])));
        }
        putchar('\n');
        fflush(stdout);
}

fxdpnt *arb_add_precision(fxdpnt *flt, size_t more)
{
        // Increase the precision of an arb `fxdpnt'
        flt = arb_expand(flt, flt->len + more);
        memset(flt->number + flt->len, 0, more * sizeof(ARBT));
        flt->len += more;
        return flt;
}
size_t rr(fxdpnt *flt)
{
        /* Right hand radix position */
        return flt->len - flt->lp;
}

size_t rl(fxdpnt *flt)
{
        /* Left hand radix position */
        return flt->lp;
}


void arb_init(fxdpnt *flt)
{
        flt->sign = '+';
        flt->len = flt->lp = 0;
}

void arb_flipsign(fxdpnt *flt)
{
        if (flt->sign == '+')
                flt->sign = '-';
        else if (flt->sign == '-')
                flt->sign = '+';
}

void arb_setsign(fxdpnt *a, fxdpnt *b, fxdpnt *c)
{
        arb_init(c);
        if (a->sign == '-')
                arb_flipsign(c);
        if (b->sign == '-')
                arb_flipsign(c);
}

void verbose(char *msg)
{
	if (verbosity)
		fprintf(stderr, "%s\n", msg);
}

int arb_highbase(int a)
{
	// Handle high bases
        static int uglyphs[36] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
                                '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                                'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; 
        if (a < 36) 
              	return uglyphs[a]; 
        else // just use the ascii values for bases that are very high
                return a;
}


void arb_print(fxdpnt *flt)
{
        size_t i = 0;
	size_t len = 0;
	flt->len = flt->lp + flt->rp;

	if (flt->len == 0)
		len = flt->lp + flt->rp;
	else
		len = flt->len;

        if (flt->sign == '-')
                putchar(flt->sign);
        for (i = 0; i < len ; ++i){
                if (flt->lp == i)
                        putchar('.');
                putchar(arb_highbase((flt->number[i])));
        }
        putchar('\n');
        fflush(stdout);
}

void arb_error(char *message)
{
        fprintf(stderr, "%s\n", message);
        exit(1);
}

void *arb_malloc(size_t len)
{
        void *ret;
        if(!(ret = malloc(len)))
                arb_error("malloc failed\n");
        return ret;
}
fxdpnt *arb_alloc(size_t len)
{
        // Allocate the basic requirements of a arb `fxdpnt'
        fxdpnt *ret = arb_malloc(sizeof(fxdpnt));
        ret->number = arb_malloc(sizeof(int) * len);
        ret->sign = '+';
        ret->lp = 0;
        ret->allocated = len;
        ret->len = 0;
        ret->chunk = 4; // set to 4 to force worst case tests, change to >255
        return ret;
}

void *arb_realloc(void *ptr, size_t len)
{
        void *ret;
        if(!(ret = realloc(ptr, len)))
                arb_error("realloc failed\n");
        return ret;
}

fxdpnt *arb_expand(fxdpnt *flt, size_t request)
{
        // Enlarge or create a fxdpnt
        if (flt == NULL){
                flt = arb_alloc(request);
		flt->allocated = request;
        } else if (request > flt->allocated){
                flt->allocated = (request + flt->chunk);
                flt->number = arb_realloc(flt->number, flt->allocated * sizeof(ARBT));
        }
        return flt;
}

fxdpnt *arb_new_num (int length, int scale)
{
	fxdpnt *ret;
	ret = arb_malloc(sizeof(fxdpnt));
	ret->sign = '+';
	ret->lp = length;
	ret->rp = scale;
	ret->allocated = 0;
	ret->len = ret->lp + ret->rp;
	ret->number = arb_malloc(length+scale);
	ret->chunk = 4;
	memset(ret->number, 0, length+scale);
	return ret;
}

void arb_free_num (fxdpnt *num)
{
	if (num == NULL)
		return;
	if ((num)->number)
		free ((num)->number);
	free (num);
	num = NULL;
}
fxdpnt *arb_mul(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
        int i = 0, j = 0, sum = 0, carry = 0;
        size_t k = 0;
        //arb_setsign(a, b, c);
        c = arb_expand(c, a->len + b->len);
        memset(c->number, 0, a->len + b->len);

        for ( i = a->len - 1; i >= 0 ; i--){
                for ( j = b->len - 1, k = i + j + 1, carry = 0; j >= 0 ; j--, k--){
                        sum = (a->number[i]) * (b->number[j]) + (c->number[k]) + carry;
                        carry = sum / base;
                        c->number[k] = (sum % base);
                }
                c->number[k] += carry;
        }
        c->len = a->len + b->len;
        c->lp = a->lp + b->lp;
        return c;
}

fxdpnt *arb_division(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale)
{
        size_t i = 0;
        size_t j = 0;
        size_t z = 0;
        size_t width = a->len + b->len;
        size_t diff = 0;
        size_t off = 0;
        char *mir = arb_malloc(sizeof(ARBT) *( width + scale));
        char *tmir = arb_malloc(sizeof(ARBT) * width);
        int sum = 0;
        int rec = 0;
        size_t iterations = 0;
        size_t adds = 0;

	c = arb_expand(c, a->len + b->len);
        arb_init(c);
        arb_setsign(a, b, c);
        
        memset(mir + a->len, 0, width - a->len + scale);
        memcpy(mir, a->number, a->len);
        c->number[z] = 0;

        /* count the zeros to the right of the radix before a non-zero value */
        while (b->number[off] == 0 && off < b->len)
                ++off;

        if (rl(a) < rl(b))
        {
                diff = rl(b) - rl(a) - 1;
                memset(c->number, 0, diff);
                c->len = z = diff;
                c->lp = 0 + off;
                c->number[z] = 0;
        }
        else {
                c->lp = rl(a) - rl(b) + off + 1;
        }

        for (; z < a->len + diff;)
        {
                for (rec = 0, i = off, j = z - diff ; i < b->len ; j++ ,i++)
                {
                        ++adds;
                        sum = (mir[j]) - (b->number[i]);
                        if (sum < 0)
                        {
                                if (j == z - diff)
                                {
                                        mir[j + 1] += ((mir[j]) * base);
                                        z++;
                                        c->len++;
                                        c->number[z] = 0;
                                }
                                else
                                {
                                        mir[j - 1] -= 1;
                                        mir[j] += base;
                                }
                                rec = 1;
                                break;

                        }
                        
                        tmir[j] = sum;
                }
                if (rec == 0)
                {
                        memcpy(mir, tmir, j);
                        c->number[z] += 1;
                }
                ++iterations;
        }
	if (verbosity)
	{
	        printf("%zu iterations\n", iterations);
	        printf("%zu adds\n", adds);
	}
        free(mir);
        free(tmir);
        return c;
}

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

fxdpnt *arb_str2fxdpnt(const char *str)
{
        // Convert a string to a arb `fxdpnt'
        size_t i = 0; 
        int flt_set = 0, sign_set = 0;

        fxdpnt *ret = arb_expand(NULL, 1);
	ret->len =0;
	ret->lp =0;
	ret->rp =0;

        for (i = 0; str[i] != '\0'; ++i){
                if (str[i] == '.'){
                        flt_set = 1;
                        ret->lp = i - sign_set;
                }
                else if (str[i] == '+'){
                        sign_set = 1;
                        ret->sign = '+';
                }
                else if (str[i] == '-'){
                        sign_set = 1;
                        ret->sign = '-';
                }
                else{
                        ret = arb_expand(ret, ret->len + 1);
                        ret->number[ret->len++] = str[i] - '0';
                }
        }

        if (flt_set == 0) 
                ret->lp = ret->len;

        ret->rp = ret->len - ret->lp;


        return ret;
}

