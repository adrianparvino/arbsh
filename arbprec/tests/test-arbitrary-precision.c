#include <arbprec.h>
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

	toym_print(a);
	toym_rightshift(a, 1, 0);
	toym_print(a);
	toym_rightshift(a, 3, 0);
	toym_print(a);
	
	
	

	toym_free(a);
	toym_free(b);
	toym_free(c);

	return 0;
}

