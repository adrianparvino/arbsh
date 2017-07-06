#include <gmath.h>

unsigned long gfactorial(unsigned long x)
{ 
	unsigned int c;
	unsigned long y = 1;
 
	for (c = 1; c <= x; c++)
		y *= c;
 
	return y; 
} 
unsigned long gfac(unsigned long x)
{
        unsigned int c;
        unsigned long y = 1;

        for (c = 1; c <= x; c++)
                y *= c;

        return y;
}
