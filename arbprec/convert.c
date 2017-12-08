#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_radix(int *array, size_t len, int value, int ibase, int obase)
{
	int carry = value;
	int tmp = 0;
	size_t i = 0;
	
	for (i = len; i > 0; i--)
	{
		tmp = (array[i-1] * ibase) + carry;
		array[i-1] = tmp % obase;
		carry = tmp / obase;
	}
}

int *inithexarray(char *str, size_t *len, int ibase, int obase)
{
	int *p;
	size_t k = strlen(str);
	size_t i = 0;
	p = calloc(k, sizeof (int));
	for (; i < k; i++)
		convert_radix(p, k, str[i] - '0', ibase, obase);
	*len = k;
	return p;
}

void printarray(int *a, size_t len)
{
	char glyph [16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', 
			'9', 'A', 'B', 'C', 'D', 'E', 'F' };
	size_t i = 0;
	for (; i < len; i++)
		printf("%c", glyph[a[i]]);
	printf("\n");
}

int main(int argc, char * argv[])
{
	int *c = NULL;
	size_t len;
	int ibase = 0;
	int obase = 0;
	if (argc < 4)
	{
		printf ("Usage: %s string ibase obase\n", argv[0]);
		return 1;
	}
	ibase = strtol(argv[2], 0, 0);
	obase = strtol(argv[3], 0, 0);
	c = inithexarray(argv[1], &len, ibase, obase);
	printarray(c, len);
	free (c);
	return 0;
}
