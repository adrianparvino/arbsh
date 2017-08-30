/*

base^cardinality

The total number of values possible within a given range in base N within a set
with a cardinality of C can be expressed as (N^C).

N=2
C=4
2^4 = 16 = 0000 (1)  0100 (5)  1000 (9)   1100 (13)
           0001 (2)  0101 (6)  1001 (10)  1101 (14)
           0010 (3)  0110 (7)  1010 (11)  1110 (15)
           0011 (4)  0111 (8)  1011 (12)  1111 (16)
                 

Using binary counting it is easy to prove this formula by iterating through all
possible values. In decimal (greater N) or with a greater cardinality (greater 
C) the table of values would be much larger --however the formula for computing
the total amount of unique values the number can hold is the same.

This formula (N^C) allows for fast and logical computation of probabilities in
a non-deterministic setting such as a dice game throwing "random" dice throws.

Here is an explanation of the probability of obtaining the sequence
 4, 6, 2, 5, 7, 9, 8 out of a random throwing of 7 dice: 

6 sided dice use a base 5 counting system consisting of the character values 1-6
(1,2,3,4,5 and 6). Therefore computing the maximum number of possible dice
combinations in base 5 using 7 dice is simple and can be expressed as the value 
5555555 (or 6666666). Therefore the entire range of this number system sits
between 0000000 and 5555555 possibilities in base 5. The possibility of such a
a roll is therefore 1/(5^7).

Normally '^' powers in C are computed using pow() from libm and the math.h
header. However because we are going to use size_t in this case to represent our
counting base pow() itself is unsuitable. The function usign_pow presented below
is sufficient for calculating base*cardinality which is never negative nor
consisting of fractional parts. (support for fractions in pow requires exp and
log and is not covered here).

*/


	#include <stdio.h>

	size_t safe_division(size_t i, size_t x)
	{
		if (i==0)
		{
			fprintf(stderr, "Divide by zero forced to return 0\n"); 
			return 0;
		}
		return i / x;
	}

	size_t safe_multiply(size_t i, size_t x, size_t lim)
	{
		size_t tmp = safe_division(lim, i);
		if (tmp >= x)
	        {
	                fprintf(stderr, "Muliplication proposal accepted\n");
	                return i * x;
	        }else if (tmp == 0)
			return 0;
	        fprintf(stderr, "Muliplication proposal rejected\n");
	        return lim;
	}

	size_t safe_upow(size_t x, size_t n)
	{
	        size_t y = 1;
	        while (n--)
			y = safe_multiply(y, x, (size_t)-1);
	        return y;
	}

	int main(void)
	{
		size_t base = 2;
		size_t cardinality = 128;
		printf("total range of brute elements %zu\n", safe_upow(base, cardinality));
		return 0;
	}

