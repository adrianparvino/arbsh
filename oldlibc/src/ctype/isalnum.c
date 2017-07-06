#include <gctype.h>
int gisalnum(int x)
{ 
	if (gisalpha(x) || gisdigit(x))
		return 1;
	return 0;
}
