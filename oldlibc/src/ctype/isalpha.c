#include <gctype.h>

int gisalpha(int x) 
{ 
	if (gisupper(x) || gislower(x))
		return 1;
	return 0;
}
