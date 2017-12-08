#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int * inithexarray(char *pDecStr, int *pnElements);
static void adddecvalue(int *pMyArray, int nElements, int value);
static void printarray(int *pHexArray, int nElements);

static void adddecvalue(int *pHexArray, int nElements, int value)
{
	int carryover = value;
	int tmp = 0;
	int i; 
	
	for (i = nElements-1; i >= 0; i--)
	{
		tmp = (pHexArray[i] * 10) + carryover;
		pHexArray[i] = tmp % 16;
		carryover = tmp / 16;
	}
}

static int *inithexarray(char *pDecStr, int *pnElements)
{
	int *pArray = NULL;
	int lenDecStr = strlen(pDecStr);
	int i = 0;
	pArray = calloc(lenDecStr,  sizeof (int));

	for (; i < lenDecStr; i++)
		adddecvalue(pArray, lenDecStr, pDecStr[i] - '0');

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

	if (argc < 2)
	{
		printf ("Usage: %s decimalString\n", argv[0]);
		return 1;
	}

	pMyArray = inithexarray (argv[1], &nElements);

	printarray (pMyArray, nElements);

	if (pMyArray != NULL)
		free (pMyArray);

	return 0;
}
