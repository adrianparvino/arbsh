#include <stdio.h>
#include <string.h>
#include <stdlib.h>





static void adddecvalue(int *pHexArray, int nElements, int value, int ibase, int obase)
{
	int carry = value;
	int tmp = 0;
	int i; 
	
	for (i = nElements-1; i >= 0; i--)
	{
		//tmp = (pHexArray[i] * 10) + carry;
		//pHexArray[i] = tmp % 16;
		//carry = tmp / 16;
		
		tmp = (pHexArray[i] * ibase) + carry;
		pHexArray[i] = tmp % obase;
		carry = tmp / obase;
	}
}

static int *inithexarray(char *pDecStr, int *pnElements, int ibase, int obase)
{
	int *pArray = NULL;
	int lenDecStr = strlen(pDecStr);
	int i = 0;
	pArray = calloc(lenDecStr, sizeof (int));

	for (; i < lenDecStr; i++)
		adddecvalue(pArray, lenDecStr, pDecStr[i] - '0', ibase, obase);

	*pnElements = lenDecStr;

	return pArray;
}

static void printarray(int *pHexArray, int nElements)
{
	
	char HexChar [16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', 
			'9', 'A', 'B', 'C', 'D', 'E', 'F' };
	int i = 0;
	for (; i < nElements; i++)
		printf ("%c", HexChar[pHexArray[i]]);
	printf ("\n");
}

int main(int argc, char * argv[])
{
	int *pMyArray = NULL;
	int nElements;
	int ibase = 0;
	int obase = 0;

	if (argc < 2)
	{
		printf ("Usage: %s decimalString\n", argv[0]);
		
		return 1;
	}
	ibase = strtol(argv[2], 0, 0);
	obase = strtol(argv[3], 0, 0);
	pMyArray = inithexarray(argv[1], &nElements, ibase, obase);
	printarray(pMyArray, nElements);
	free (pMyArray);
	return 0;
}
