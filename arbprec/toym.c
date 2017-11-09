// Fixed-point arbitrary precision long hand algorithms written by
// Christopher M. Graff for Rob Landley's `toybox' project.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {          // Toym fxdpnt type
        char *number;     // The actual number
        int sign;         // Sign
        size_t lp;        // Length left of radix
        size_t rp;
        size_t len;       // Length of number (count of digits / limbs)
        size_t allocated; // Length of allocated memory
        size_t chunk;     // Allocation chunk size
} fxdpnt;

#define MAX(a,b)      ((a)>(b)?(a):(b))
#define MIN(a,b)      ((a)>(b)?(b):(a))
#define TOYMT char 


fxdpnt *toym_div(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_mul(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_add_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_sub_inter(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_add(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_add(fxdpnt *, fxdpnt *, fxdpnt *, int);
fxdpnt *toym_expand(fxdpnt *, size_t);
fxdpnt *toym_str2fxdpnt(const char *);
fxdpnt *toym_add_precision(fxdpnt *, size_t);
fxdpnt *toym_alloc(size_t);
fxdpnt *toym_div3(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base);
void *toym_malloc(size_t);
void *toym_realloc(void *, size_t);

void toym_reverse(char *, size_t);
void toym_flipsign(fxdpnt *);
void toym_setsign(fxdpnt *, fxdpnt *, fxdpnt *);
void toym_init(fxdpnt *);
void toym_print(fxdpnt *);
void toym_free(fxdpnt *);
void toym_error(char *);


int toym_highbase(int);
int toym_place(fxdpnt *, fxdpnt *, size_t *, size_t);
int toym_compare(fxdpnt *a, fxdpnt *b, int base);
fxdpnt *toym_division(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale);
fxdpnt *toym_rightshift(fxdpnt *a, size_t n, int faux);
fxdpnt *toym_leftshift(fxdpnt *a, size_t n);

fxdpnt *toym_rightshift(fxdpnt *a, size_t n, int faux)
{ 
	/* logical right shift, turns base 10 "990" into "099" 
		else
	   "faux" logical shift turns "990" into "99"
	*/
	size_t i = 0;
	size_t j = a->len - n - 1;
	size_t k = a->len - 1;
	size_t l = 0;

	if (faux == 0)
	{
		for (i = n-1;i < a->len-1; ++i, --j, --k) 
			a->number[k] = a->number[j];
		
		while (n-- > 0)
			a->number[l++] = 0;
	}
	else {
		while (n--&& a->len > 0)
			a->len--;
	}
	return a;
}

fxdpnt *toym_leftshift(fxdpnt *a, size_t n)
{
	// not implemented
	return a;
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


// helper functions that could be replaced or hard coded
int toym_highbase(int a)
{
        // Handle high bases
        static int uglyphs[36] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
                                '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                                'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        if (a <= 36)
                return uglyphs[a];
        else // just use the ascii values for bases that are very high
                return a;
}

fxdpnt *toym_alloc(size_t len)
{
	// Allocate the basic requirements of a toym `fxdpnt'
	fxdpnt *ret = toym_malloc(sizeof(fxdpnt));
	ret->number = toym_malloc(sizeof(TOYMT) * len);
	ret->sign = '+';
	ret->lp = 0;
	ret->allocated = len;
	ret->len = 0;
	ret->chunk = 4; // set to 4 to force worst case tests, change to >255
	return ret;
}

void toym_init(fxdpnt *flt)
{
	flt->sign = '+';
	flt->len = flt->lp = 0;
}

void toym_flipsign(fxdpnt *flt)
{
	if (flt->sign == '+')
		flt->sign = '-';
	else if (flt->sign == '-')
		flt->sign = '+';
}

void toym_print(fxdpnt *flt)
{
	size_t i = 0;
	
	if (flt->sign == '-')
		putchar(flt->sign);
	for (i = 0; i < flt->len ; ++i){
		if (flt->lp == i)
			putchar('.');
		putchar(toym_highbase((flt->number[i])));
	}
	putchar('\n');
	fflush(stdout);
}

fxdpnt *toym_str2fxdpnt(const char *str)
{
	// Convert a string to a toym `fxdpnt'
	size_t i = 0;
	int flt_set = 0, sign_set = 0;

	fxdpnt *ret = toym_expand(NULL, 1);

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
			ret = toym_expand(ret, ret->len + 1);
			ret->number[ret->len++] = str[i] - '0';
		}
	}
 
	if (flt_set == 0)
		ret->lp = ret->len;

	//ret->lp = ret->len - ret->lp;
	ret->rp = ret->len - ret->lp;
	

	return ret;
}

void toym_free(fxdpnt *flt)
{
	if (flt->number)
		free(flt->number);
	free(flt);
}

fxdpnt *toym_expand(fxdpnt *flt, size_t request)
{
	// Enlarge or create a fxdpnt
	if (flt == NULL){
		flt = toym_alloc(request);
	} else if (request > flt->allocated){
		flt->allocated = (request + flt->chunk);
		flt->number = toym_realloc(flt->number, flt->allocated * sizeof(TOYMT));
	}
	return flt;
}

fxdpnt *toym_add_precision(fxdpnt *flt, size_t more)
{
	// Increase the precision of a toym `fxdpnt'
	flt = toym_expand(flt, flt->len + more);
	memset(flt->number + flt->len, 0, more * sizeof(TOYMT));
	flt->len += more;
	return flt;
}

void toym_error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void *toym_malloc(size_t len)
{
	void *ret;
	if(!(ret = malloc(len)))
		toym_error("malloc failed\n");
	return ret;
}

void *toym_realloc(void *ptr, size_t len)
{
	void *ret;
	if(!(ret = realloc(ptr, len)))
		toym_error("realloc failed\n");
	return ret;
}

void toym_setsign(fxdpnt *a, fxdpnt *b, fxdpnt *c)
{
	toym_init(c);
	if (a->sign == '-')
		toym_flipsign(c);
	if (b->sign == '-')
		toym_flipsign(c);
}

int toym_place(fxdpnt *a, fxdpnt *b, size_t *cnt, size_t r)
{
	/* many arbitrary precision implementations go through four steps
	   instead of "crossing over the values" like one does on pen and paper.
	   In theory this should be slower, however, in my simple test runs
	    is has matched the speed of the "four step" techniques.
	*/
	int temp = 0;
	// exhaust the difference between the right hand sides of the radi
	if ((a->len - a->lp) < (b->len - b->lp))
		if( (b->len - b->lp) - (a->len - a->lp) > r)
			return 0;
	// offset mechanism for varying number lengths
	if (*cnt < a->len){
		temp = a->number[a->len - *cnt - 1];
		(*cnt)++; // not ideal but better than a seperate ret struct
		return temp;
	}
	(*cnt)++;
	// exhaust the difference between the left hand sides of the radi
	return 0;
}

void toym_reverse(char *x, size_t lim)
{
	size_t i = 0, half = lim / 2;
	int swap = 0;
	for (;i < half; i++){
		swap = x[i];
		x[i] = x[lim - i - 1];
		x[lim - i - 1] = swap;
	}
}

fxdpnt *toym_add(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	toym_init(c);
	if (a->sign == '-' && b->sign == '-')
		toym_flipsign(c);
	else if (a->sign == '-')
		return c = toym_sub_inter(b, a, c, base);
	else if (b->sign == '-')
		return c = toym_sub_inter(a, b, c, base);
	return c = toym_add_inter(a, b, c, base);
}

fxdpnt *toym_sub(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	toym_init(c);
	if (a->sign == '-' && b->sign == '-')
		toym_flipsign(c);
	else if (a->sign == '-'){
		toym_flipsign(c);
		return c = toym_add_inter(a, b, c, base);
	}
	else if (b->sign == '-' || a->sign == '-')
		return c = toym_add_inter(a, b, c, base);
	return c = toym_sub_inter(a, b, c, base);
}
 

fxdpnt *toym_add_inter(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{ 
	size_t width = 0, i = 0, j = 0, r = 0;
	int sum = 0, carry = 0;

	c->lp = MAX(a->lp, b->lp);
	width = MAX(a->len, b->len);
	c = toym_expand(c, width * 2);

	for (; i < a->len || j < b->len;c->len++, ++r){
		sum = toym_place(a, b, &i, r) + toym_place(b, a, &j, r) + carry;
		carry = 0;
		if(sum >= base){
			carry = 1;
			sum -= base;
		}
		c->number[c->len] = sum;
	}
	if (carry){
		c->number[c->len++] = 1;
		c->lp += 1;
	}
	
	toym_reverse(c->number, c->len);
	return c;
}

fxdpnt *toym_sub_inter(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{ 
	size_t width = 0, i = 0, j = 0, r = 0;
	int sum = 0, borrow = 0;
	int mborrow = -1; // mirror borrow must be -1
	int mir = 0;
	size_t z = 0, y = 0; // dummy variables for the mirror
	char *array;

	c->lp = MAX(a->lp, b->lp);
	width = MAX(a->len, b->len);
	c = toym_expand(c, width * 2); // fixme: this is way oversized

	array = toym_malloc((width * 2) * sizeof(TOYMT)); // fixme: this is way oversized

	for (; i < a->len || j < b->len;c->len++, ++r){
		mir = toym_place(a, b, &y, r) - toym_place(b, a, &z, r) + mborrow; // mirror
		sum = toym_place(a, b, &i, r) - toym_place(b, a, &j, r) + borrow;

		borrow = 0;
		if(sum < 0){
			borrow = -1;
			sum += base;
		}
		c->number[c->len] = sum;
		// maintain a mirror for subtractions that cross the zero threshold
		y = i;
		z = j;
		mborrow = 0;
		if(mir < 0){
			mborrow = -1;
			mir += base;
		}
		array[c->len] = (base-1) - mir;
	}
	// a left over borrow indicates that the zero threshold was crossed
	if (borrow == -1){ 
		// swapping pointers would make this faster
		memcpy(c->number, array, c->len);
		toym_flipsign(c);
	}
	free(array);
	toym_reverse(c->number, c->len);
	return c;
}
char divu10(char n) {
    char q, r;
    q = (n >> 1) + (n >> 2);
    q = q + (q >> 4);
    q = q + (q >> 8);
    q = q + (q >> 16);
    q = q >> 3;
    r = n - (((q << 2) + q) << 1);
    return q + (r > 9);
}


fxdpnt *toym_mul(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base)
{
	int i = 0, j = 0, sum = 0, carry = 0;
	size_t k = 0;
	size_t inner = 0;
	size_t outer = 0;

	toym_setsign(a, b, c);
	c = toym_expand(c, a->len + b->len);
	memset(c->number, 0, a->len + b->len);

	for ( i = a->len - 1; i >= 0 ; i--){
		for ( j = b->len - 1, k = i + j + 1, carry = 0; j >= 0 ; j--, k--){
			sum = (a->number[i]) * (b->number[j]) + (c->number[k]) + carry;
			carry = sum / base;
			
			//carry = sum >> 1;
			//carry = divu10(sum);
			
			c->number[k] = (sum % base);
			//c->number[k] = (sum & (base-1));
			++inner;
		}
		c->number[k] += carry;
		++outer;
	}
	c->len = a->len + b->len;
	c->lp = a->lp + b->lp;
	return c;
}


fxdpnt *toym_division(fxdpnt *a, fxdpnt *b, fxdpnt *c, int base, int scale)
{
	size_t i = 0;
	size_t j = 0;
	size_t z = 0;
	size_t width = a->len + b->len;
	size_t diff = 0;
	size_t off = 0;
	char *mir = toym_malloc(sizeof(TOYMT) *( width + scale));
	char *tmir = toym_malloc(sizeof(TOYMT) * width);
	int sum = 0;
	int rec = 0;
	size_t iterations = 0;
	size_t adds = 0;

	toym_init(c);
	toym_setsign(a, b, c);
	c = toym_expand(c, a->len + b->len);
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
	
	for ( ; z < a->len + diff; )
	{
		
		for (rec = 0, i = off, j  = z - diff ; i < b->len ; j++ ,i++)
		{
			++adds;
			sum = (mir[j]) - (b->number[i]);
			if ( sum < 0 )
			{ 
				if ( j == z - diff)
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
			else
				tmir[j] = sum;
		}
		if ( rec == 0 )
		{
			memcpy(mir, tmir, j);
			c->number[z] += 1;
			
		}
		++iterations;
	} 
	printf("%zu iterations\n", iterations);
	printf("%zu adds\n", adds);
	free(mir);
	free(tmir);
	return c;
}


int main(int argc, char *argv[])
{
	if (argc < 5 )
		toym_error("Needs 4 args, such as:  123 / 123 base scale");
 
	size_t scale =  strtol(argv[5], 0, 10);
	int base = strtol(argv[4], 0, 10);
	fxdpnt *a, *b, *c;

	a = toym_str2fxdpnt(argv[1]);
	b = toym_str2fxdpnt(argv[3]);
	
	//a = toym_add_precision(a, scale);
	//b = toym_add_precision(b, scale);
	c = toym_expand(NULL, 1);

	// multiplication
	if (strcmp(argv[2], "*") == 0)
	{
		c = toym_mul(a, b, c, base);
		toym_print(c);
	}
	// division
	if (strcmp(argv[2], "/") == 0)
	{ 
		c = toym_division(a, b, c, base, scale);
		toym_print(c); 
	}

	// addition
	if (strcmp(argv[2], "+") == 0)
	{
		c = toym_add(a, b, c, base);
		toym_print(c);
	}
	// subtraction
	if (strcmp(argv[2], "-") == 0)
	{
		c = toym_sub(a, b, c, base);
		toym_print(c);
	}
	/*
	toym_print(a);
	toym_rightshift(a, 1, 0);
	toym_print(a);
	toym_rightshift(a, 3, 0);
	toym_print(a);
	*/
	printf("length of a is %zu\n", a->len);
	toym_rightshift(a, 5, 1);
	printf("length of a is %zu\n", a->len);
	toym_free(a);
	toym_free(b);
	toym_free(c);

	return 0;
}
