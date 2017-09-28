/*
c-safety (Unsigned pow 12.0 ((pow(base, floor(log10(x))+1)-1)))          page 15

The total number of values possible within a given range in base N can be
expressed as ((pow(base, floor(log10(x))+1)-1)) or (N^C) where C is the 
cardinality of the set.

N=2
C=4

scientfic
notation   decimal    binary

2^4    =   16    =    0000 (1)  0100 (5)  1000 (9)   1100 (13)
                      0001 (2)  0101 (6)  1001 (10)  1101 (14)
                      0010 (3)  0110 (7)  1010 (11)  1110 (15)
                      0011 (4)  0111 (8)  1011 (12)  1111 (16)


Using binary counting it is easy to prove this formula by iterating through all
possible values. In decimal (greater N) or with a greater cardinality (greater
C) the table of values would be much larger --however the formula for computing
the total amount of unique values the number can hold is the same.
*/


	#include <stdio.h>

	size_t safe_division(size_t i, size_t x)
	{
		if (x==0)
		{
			fprintf(stderr, "Divide by zero rejected\n");
			return i;
		}
		return i / x;
	}
/*
The C standard specifies that unsigned integer types must wrap around when they
hit their maximum limit. However it is possible to keep this from happening by 
carefully precomputing each calculation to see that it can fit.  The limit of a
given size is computed with (T)-1. The function safe_multiply provides safe
bounded multiplication.
*/
	size_t safe_multiply(size_t i, size_t x, size_t lim)
	{
		size_t tmp = safe_division(lim, i);
		if (tmp >= x)
	        {
	                fprintf(stderr, "Multiplication proposal accepted\n");
	                return i * x;
	        }else if (tmp == 0)
			return 0;
	        fprintf(stderr, "Multiplication proposal rejected\n");
	        return lim;
	}

	size_t safe_upow(size_t b, size_t c)
	{
	        size_t ret = 1;
	        while (c--)
			ret = safe_multiply(ret, b, (size_t)-1);
	        return ret;
	}

	int main(void)
	{
		size_t b = 2;
		size_t c = 4;
		printf("total range of brute elements %zu\n", safe_upow(b, c));
		return 0;
	}

/*
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
*/
