#include <math.h>

unsigned long factorial(unsigned long x)
{ 
	unsigned int c;
	unsigned long y = 1;
 
	for (c = 1; c <= x; c++)
		y *= c;
 
	return y; 
} 
unsigned long fac(unsigned long x)
{
        unsigned int c;
        unsigned long y = 1;

        for (c = 1; c <= x; c++)
                y *= c;

        return y;
}
