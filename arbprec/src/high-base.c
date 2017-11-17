#include <arbprec.h>

int arb_highbase(int a)
{
	// Handle high bases
	static int uglyphs[36] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
				'9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
				'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
				'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	if (a < 36) 
		return uglyphs[a]; 
	else // just use the ascii values for bases that are very high
		return a;
}

