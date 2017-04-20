#include <arb_str/arb_str.h>
#include <stdio.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
	
	char *string;
	char *y;
	char *z;
	y = mirror = arb_str_malloc(1000);
	z = string = arb_str_malloc(1000);

	if (argc < 3)
	{
		dprintf(2, "%s", "Please supply two args\n");
		return 1;
	}

	printf("\n\n%s / %s\n", argv[1], argv[2]); 
	string[0] = 0;
	string = arb_str_divide(argv[1], argv[2], string);
	printf("answer (strtod) %lf\n", strtod(argv[1], 0) / strtod(argv[2], 0) );
	printf("result          %s\n", string);

	printf("\n\n%s + %s\n", argv[1], argv[2]); 
	string[0] = 0;
	string = arb_str_add(argv[1], argv[2], string);
	printf("answer (strtod) %lf\n", strtod(argv[1], 0) + strtod(argv[2], 0) );
	printf("result          %s\n", string);

	printf("\n\n%s - %s\n", argv[1], argv[2]); 
	string[0] = 0;
	string = arb_str_subtract(argv[1], argv[2], string);
	printf("answer (strtod) %lf\n", strtod(argv[1], 0) - strtod(argv[2], 0) );
	printf("result          %s\n", string);

	
	printf("\n\n%s * %s\n", argv[1], argv[2]); 
	string[0] = 0;
	string = arb_str_multiply(argv[1], argv[2], string);
	printf("answer (strtod) %lf\n", strtod(argv[1], 0) * strtod(argv[2], 0) );
	printf("result          %s\n", string);
	free(z);
	free(y);
	return 0;
}
